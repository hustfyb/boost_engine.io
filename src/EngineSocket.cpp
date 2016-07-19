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
	transport_->sid = id_;
	sendPacket(open, JSON.stringify({
	sid: this.id
		 , upgrades : this.getAvailableUpgrades()
		, pingInterval : this.server.pingInterval
		, pingTimeout : this.server.pingTimeout
	}));

	this.emit('open');
	this.setPingTimeout();
}
