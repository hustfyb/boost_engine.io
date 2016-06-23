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
	pt_root.add_child("upgrade",upgrade);

	std::stringstream ss;
	boost::property_tree::write_json(ss, pt_root,false);
	std::string s = ss.str();

	encodePacket(open, s);

	//response.sendData()
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
