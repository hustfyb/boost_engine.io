#include "header.hpp"
#include "engineIo.hpp"
#include "engineIoParser.hpp"
#include "PollTranser.h"
using namespace engineIoParser;
#include <boost/unordered_map.hpp>
unordered_map<std::string, shared_ptr<session_t> > sessionStore;
EngineIo::EngineIo()
{
	pingTimeout = 60000;
	pingInterval = 25000;
	//upgradeTimeout : 10000,
}

void EngineIo::sendErrorMessage(Request&request, Response&response, code) {
	response.setHeader("Content-Type","application/json");
	if (request.header.find("Origin")) {
		response.setHeader("Access-Control-Allow-Origin"), request.header["Origin"]);
		response.setHeader("Access-Control-Allow-Credentials"), std::string("true"));
	}
	else
	{
		response.setHeader(std::string("Access-Control-Allow-Origin"), std::string("*"));

	}

// 	res.writeHead(400, headers);
// 	res.end(JSON.stringify({
// 	code: code,
// 		  message : Server.errorMessages[code]
// 	}));
}
void EngineIo::process(Request&request, Response&response, Callback cb)
{
 	if (request.query.find("sid") != request.query.end()) {
		if (sessionStore.find(request.query["sid"])) {

			sessionStore[request.query["sid"]]->request = &request;
			sessionStore[request.query["sid"]]->response = &response;
			request.m_parse.method == HTTP_POST
		}else {

		}
 	}
 	else {
		handleHandShake(request, response, cb);
 	}

}

void EngineIo::handleHandShake(Request& request, Response& response, Callback cb)
{
	uuid_t uid;
	shared_ptr<session_t> session = make_shared<session_t>();
	session->sid = uid.toString().substr(0, 20);
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
	response.setHeader(std::string("Access-Control-Allow-Origin"), request.header["Origin"]); 
	response.setHeader(std::string("Access-Control-Allow-Credentials"), std::string("true"));
	response.sendData(payload,cb);
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
