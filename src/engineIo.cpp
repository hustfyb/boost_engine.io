#include "header.hpp"
#include "engineIo.hpp"
#include "engineIoParser.hpp"
#include "PollTranser.hpp"
using namespace engineIoParser;
#include <boost/unordered_map.hpp>
unordered_map<std::string, shared_ptr<session_t> > sessionStore;
EngineIo::EngineIo()
{
	pingTimeout = 60000;
	pingInterval = 25000;
	//upgradeTimeout : 10000,
}

void EngineIo::sendErrorMessage(Request &request, Response&response, int code,Callback cb) {
	response.setHeader("Content-Type","application/json");
	response.setCross(request);
	response.setStatus(Response::bad_request);
	property_tree::ptree pt_root;
	pt_root.put("code", code);
	pt_root.put("message", errorMessages[code]);
	std::stringstream ss;
	boost::property_tree::write_json(ss, pt_root, false);
	std::string s = ss.str();
	response.sendData(s, cb);
}

int EngineIo::verify(Request&request, Response&response) {
	// transport check
	if (request.query.find("transport") == request.query.end() 
		|| !TranserBase::existTranser(request.query["transport"])
		)
	{
		LOG(error) << "unknown transport " << request.query["transport"];
		return Errors::UNKNOWN_TRANSPORT;
	}
	
	// sid check
	auto _sidIter = request.query.find("sid");
	if (_sidIter != request.query.end())
	{
		if (sessionStore.find(_sidIter->second) == sessionStore.end())
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

void EngineIo::process(Request&request, Response&response, Callback cb)
{
	int checkCode = verify(request, response);
	if (checkCode == Errors::ERROR_OK) {
		if (request.query.find("sid") != request.query.end()) {
			sessionStore[request.query["sid"]]->transport->onRequest(request,response,cb);
		}
		else
		{
			handleHandShake(request, response, cb);
		}
	}
	else
	{
		sendErrorMessage(request, response, checkCode,cb);
	}
}

void EngineIo::handleHandShake(Request& request, Response& response, Callback cb)
{
	uuid_t uid;
	shared_ptr<session_t> session = make_shared<session_t>();
	session->sid = uid.toString();
	sessionStore[session->sid] = session;

	property_tree::ptree pt_root;
	pt_root.put("sid", session->sid);
	pt_root.put("pingInterval", this->pingInterval);
	pt_root.put("pingTimeout", this->pingTimeout);
	property_tree::ptree upgrade;
	property_tree::ptree method;
	method.put("","");
	upgrade.push_back(std::make_pair("", method));
	pt_root.add_child("upgrades",upgrade);
	std::stringstream ss;
	boost::property_tree::write_json(ss, pt_root,false);
	std::string s = ss.str();
	std::string payload = encodePayloadAsBinary(encodePacket(open, s));

	session->transport = make_shared<PollTranser>(); //default PollTranser

	response.setHeader(std::string("Content-Type"), std::string("application/octet-stream"));
	response.setCross(request);
	response.sendData(payload,cb);
	LOG(info) << "handshake " << ss.str();
	return ;
}

// engineIo::engineIo()
// {
// }
// 
// 
// engineIo::~engineIo()
// {
// }
