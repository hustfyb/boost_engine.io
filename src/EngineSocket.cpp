#include "header.hpp"
#include "EngineSocket.hpp"


EngineSocket::EngineSocket(std::string &id,shared_ptr<TranserBase> transport,RequestPtr request,ResponsePtr response):
	id_(id),
	request_(request),
	response_(response),
	transport_(transport)
{
	upgrading_ = false;
	upgraded_ = false;
	readyState_ = opening;

	onOpen();
}


EngineSocket::~EngineSocket()
{
}

void EngineSocket::onOpen()
{
	readyState_ = open;

	// sends an `open` packet
	transport_->id_ = id_;

	property_tree::ptree pt_root;
	pt_root.put("sid", session->sid);
	pt_root.put("pingInterval", this->pingInterval);
	pt_root.put("pingTimeout", this->pingTimeout);
	property_tree::ptree upgrade;
	foreach (std::string name, TranserBase::getTranserNames())
	{
		property_tree::ptree method;
		method.put("",name);
		upgrade.push_back(std::make_pair("", method));
	}
	pt_root.add_child("upgrades",upgrade);


	// 	std::stringstream ss;
	// 	boost::property_tree::write_json(ss, pt_root,false);
	// 	std::string s = ss.str();
	// 	std::string payload = encodePayloadAsBinary(encodePacket(open, s));
	// 
	// 
	// 	response.setHeader(std::string("Content-Type"), std::string("application/octet-stream"));
	// 	response.sendData(payload,cb);
	//	LOG(info) << "handshake " << ss.str();

 	sendPacket(open, JSON.stringify({
 	sid: this.id
 		 , upgrades : this.getAvailableUpgrades()
 		, pingInterval : this.server.pingInterval
 		, pingTimeout : this.server.pingTimeout
 	}));

// 	this.emit('open');
 	this.setPingTimeout();
}
