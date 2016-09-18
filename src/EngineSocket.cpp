#include "header.hpp"
#include "EngineSocket.hpp"
#include "util.hpp"

EngineSocket::EngineSocket(std::string &id, EngineIo* engineIo, shared_ptr<TranserBase> transport,
	RequestPtr request,ResponsePtr response,io_service &ios):
	id_(id),
	engineIo_(engineIo),
	request_(request),
	response_(response),
	transport_(transport),
	timer_(ios)
{
	upgrading_ = false;
	upgraded_ = false;
	readyState_ = opening;
	//onOpen();
}


EngineSocket::~EngineSocket()
{
}

void EngineSocket::onRequest(RequestPtr request, ResponsePtr response) const
{
	if (upgrading_) {
		oldTransport_->onRequest(request, response);
	}
	else
	{
		transport_->onRequest(request, response);
	}
}

void EngineSocket::onPacket(EngineIoParser::PacketPtr paPtr)
{
	if (EngineSocket::open == this->readyState_) 
	{
		LOG(debug) << "packet";

		// Reset ping timeout on any packet, incoming data is a good sign of
		// other side's liveness
		this->setPingTimeout();

		switch (paPtr->type)
		{
		case EngineIoParser::ping:
			LOG(debug)<<"got ping "<<paPtr->data;
			transport_->sendPacket(EngineIoParser::pong,paPtr->data);
			if (upgrading_) {
				LOG(debug) << "send noop " << paPtr->data;
				oldTransport_->sendPacket(EngineIoParser::noop,std::string(""));
			}
			break;
		case EngineIoParser::upgrade:
			LOG(debug) << "upgrade";
			upgrading_ = false;
			upgraded_ = true;
			break;
 		case EngineIoParser::error:
 		 	this->onClose("parse error");
 		 	break;
		case EngineIoParser::message:
			handler_->onMessage(this, paPtr->data);
		 	break;
		}
	}
	else 
	{
		LOG(warning)<<"packet received with closed socket";
 	}
}

void EngineSocket::setPingTimeout()
{
	timer_.expires_from_now(posix_time::millisec(engineIo_->pingInterval_ + engineIo_->pingTimeout_));
	timer_.async_wait(bind(&EngineSocket::pingTimeout, shared_from_this(), asio::placeholders::error));
}

void EngineSocket::pingTimeout(const boost::system::error_code& error)
{
	if (!error)
	{
		onClose("ping timeout");
	}
}

void EngineSocket::upgrade(shared_ptr<TranserBase> transport)
{
	LOG(debug)<<"upgrade begin"<< this->transport_->name_;
	//切换时间可以研究一下
	upgrading_ = true;
	if (this->transport_->name_!="websocket") {
		this->oldTransport_ = this->transport_;
	}
	else {
		LOG(debug) << "no transport";
	}
	this->transport_ = transport;
	transport_->id_ = id_;
	transport_->setSocket(this);
}

void EngineSocket::send(std::string & data)
{
	transport_->sendPacket(EngineIoParser::message, data);
}

void EngineSocket::onOpen()
{
	readyState_ = open;

	// sends an `open` packet
	transport_->id_ = id_;
	transport_->setSocket(this);

	property_tree::ptree pt_root;
	pt_root.put("sid", id_);
	pt_root.put("pingInterval", engineIo_->pingInterval_);
	pt_root.put("pingTimeout", engineIo_->pingTimeout_);
	property_tree::ptree upgrade;
	property_tree::ptree method;
	foreach(std::string name, TranserBase::getTranserNames())
 	{
		if (name != "polling") 
		{
			method.put("", name);
			upgrade.push_back(std::make_pair("", method));
		}
 	}
	if (upgrade.size() == 0)
	{
		method.put("", "");
		upgrade.push_back(std::make_pair("", method));
	}
	pt_root.add_child("upgrades",upgrade);

	transport_->sendPacket(EngineIoParser::open, util::ptToJsonStr(pt_root));
 	this->setPingTimeout();
	handler_ = createEngineSocketHandler();
	handler_->onConnect(this);
}

void EngineSocket::onClose(char *reason)
{
	LOG(debug) << "close for " << reason;
	if (closed != readyState_) 
	{
 		this->readyState_ = closed;
		timer_.cancel();
// 		this.clearTransport();
		handler_->onClose(this);
		engineIo_->removeSocket(this->id_);

 	}
}