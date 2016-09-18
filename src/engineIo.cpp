#include "header.hpp"
#include "engineIo.hpp"
#include "EngineIoParser.hpp"
#include "PollTranser.hpp"
#include "EngineSocket.hpp"
using namespace EngineIoParser;
#include <boost/unordered_map.hpp>
#include "util.hpp"
unordered_map<std::string, shared_ptr<EngineSocket>> socketStore;

EngineIo::EngineIo(asio::io_service& ios) : ios_(ios)
{
	pingTimeout_ = 60000;
	pingInterval_ = 25000;
	//upgradeTimeout : 10000,
}

void EngineIo::sendErrorMessage(RequestPtr request, ResponsePtr response, int code) {
	response->setHeader("Content-Type","application/json");
	response->setStatus(Response::bad_request);
	property_tree::ptree pt_root;
	pt_root.put("code", code);
	pt_root.put("message", errorMessages[code]);
	std::stringstream ss;
	property_tree::write_json(ss, pt_root, false);
	std::string s = ss.str();
	response->sendData(s);
}

int EngineIo::verify(RequestPtr request) {
	// transport check
	if (request->query_.find("transport") == request->query_.end() 
		|| !TranserBase::existTranser(request->query_["transport"])
		)
	{
		BOOST_LOG_TRIVIAL(error) << "acceptor error ";
		LOG(error) << "unknown transport " << request->query_["transport"];
		return Errors::UNKNOWN_TRANSPORT;
	}
	
	// sid check
	auto _sidIter = request->query_.find("sid");
	if (_sidIter != request->query_.end())
	{
		if (socketStore.find(_sidIter->second) == socketStore.end())
		{
			LOG(error) << "can't find sid " << _sidIter->second;
			return Errors::UNKNOWN_SID;
		}
	}
	else 
	{    // handshake is GET only
		if (request->method_ != HTTP_GET) {
			LOG(error) << "wrong post for handshake";
			return Errors::BAD_HANDSHAKE_METHOD;
		}
	}
	return	Errors::ERROR_OK;
}

void EngineIo::process(RequestPtr request, ResponsePtr response)
{
	int checkCode = verify(request);
	//response->setCross(request);
	if (checkCode == Errors::ERROR_OK) {
		if (MapIsExist(request->query_,"sid")) {
			socketStore[request->query_["sid"]]->onRequest(request,response);
		}
		else
		{
			handleHandShake(request, response);
		}
	}
	else
	{
		sendErrorMessage(request, response, checkCode);
	}
}

void EngineIo::handleHandShake(RequestPtr request, ResponsePtr response)
{
	std::string transportName=MapGet(request->query_,"transport","polling");
	
	shared_ptr<TranserBase> transport(TranserBase::CreateTranserByName(transportName));
	transport->init(request, response);
 	uuid_t uid;
 	shared_ptr<EngineSocket> engineSocket = boost::make_shared<EngineSocket>(uid.toString(), this,transport,request,response,ios_);
 	socketStore[engineSocket->id_] = engineSocket;
	engineSocket->onOpen();
	return ;
}

void EngineIo::attach(shared_ptr<Server> httpServer)
{
	httpServer->addFilter(".*/engine.io/.*", shared_from_this());
}

void EngineIo::removeSocket(std::string &id)
{
	socketStore.erase(id);
}

#include "WebsocketTranser.hpp"
void EngineIo::wsOnConnect(WebSocketPtr ws)
{
	LOG(info) << ws->req_->url;
	int checkCode = verify(ws->req_);
 	if (checkCode == Errors::ERROR_OK) {
		if (MapIsExist(ws->req_->query_, "sid")) {
			shared_ptr<TranserBase> transport(TranserBase::CreateTranserByName("websocket"));
			shared_ptr<EngineSocket> socket= socketStore[ws->req_->query_["sid"]];
			socket->upgrade(transport);
			(dynamic_pointer_cast<WebsocketTranser>(transport))->setHandler(ws);
		}
	}
 	else
 	{
		//Ã»ÓÐÐ´£¿£¿£¿£¿
 	}



}

