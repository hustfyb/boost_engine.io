#include "header.hpp"
#include "engineIo.hpp"
#include "EngineIoParser.hpp"
#include "PollTranser.hpp"
#include "EngineSocket.hpp"
using namespace EngineIoParser;
#include <boost/unordered_map.hpp>
unordered_map<std::string, shared_ptr<EngineSocket>> socketStore;
#define isExist(T,K) T.find(K)!=T.end()
#define mapGet(T,K,D) isExist(T,K)?T[K]:D

EngineIo::EngineIo(asio::io_service& ios) : ios_(ios)
{
	pingTimeout_ = 6000;
	pingInterval_ = 5000;
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

int EngineIo::verify(Request &request, Response &response) {
	// transport check
	if (request.query_.find("transport") == request.query_.end() 
		|| !TranserBase::existTranser(request.query_["transport"])
		)
	{
		BOOST_LOG_TRIVIAL(error) << "acceptor error ";
		LOG(error) << "unknown transport " << request.query_["transport"];
		return Errors::UNKNOWN_TRANSPORT;
	}
	
	// sid check
	auto _sidIter = request.query_.find("sid");
	if (_sidIter != request.query_.end())
	{
		if (socketStore.find(_sidIter->second) == socketStore.end())
		{
			LOG(error) << "can't find sid " << _sidIter->second;
			return Errors::UNKNOWN_SID;
		}
	}
	else 
	{    // handshake is GET only
		if (request.method_ != HTTP_GET) {
			LOG(error) << "wrong post for handshake";
			return Errors::BAD_HANDSHAKE_METHOD;
		}
	}
	return	Errors::ERROR_OK;
}

void EngineIo::process(RequestPtr request, ResponsePtr response)
{
	int checkCode = verify(*request, *response);
	//response->setCross(request);
	if (checkCode == Errors::ERROR_OK) {
		if (request->query_.find("sid") != request->query_.end()) {
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
	LOG(debug)<<"xxxxxx";
	std::string transportName=mapGet(request->query_,"transport","polling");
	
	shared_ptr<TranserBase> transport(TranserBase::CreateTranserByName(transportName));
	transport->init(request, response);
// 	if (transport->name_ == "polling") {
// 
// 	}
 	uuid_t uid;
 	shared_ptr<EngineSocket> engineSocket = boost::make_shared<EngineSocket>(uid.toString(), this,transport,request,response,ios_);
 	socketStore[engineSocket->id_] = engineSocket;
	engineSocket->onOpen();
	return ;
}

void EngineIo::removeSocket(std::string &id)
{
	socketStore.erase(id);
}

