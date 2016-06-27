#include "header.hpp"
#include "engineIo.hpp"
#include "engineIoParser.hpp"
using namespace engineIoParser;
#include <boost/unordered_map.hpp>
unordered_map<std::string, shared_ptr<session_t> > sessionStore;
engineIo::engineIo()
{
	pingTimeout = 60000;
	pingInterval = 25000;
	//upgradeTimeout : 10000,
}

void engineIo::operator()(Request&request, Response&response, Callback cb)
{
 	if (request.query.find("sid") != request.query.end()) {
// 
 	}
 	else {
		handleHandShake(request, response, cb);
 	}

}

void engineIo::handleHandShake(Request& request, Response& response, Callback cb)
{
	uuid_t uid;
	shared_ptr<session_t> session = make_shared<session_t>();
	session->sid = uid.toString().substr(0, 20);
	sessionStore[session->sid] = session;

#if 1
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
#else
	std::string reply=("{\"sid\":\"osOqSrIF9HVWEVTmAAAE\",\"upgrades\":[],\"pingInterval\":25000,\"pingTimeout\":60000}");
	std::string payload = encodePayloadAsBinary(encodePacket(open, reply));
#endif

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
