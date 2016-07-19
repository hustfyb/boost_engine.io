#include "header.hpp"
#include "PollTranser.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "EngineIoParser.hpp"
std::vector<std::string> TranserBase::names;
RegisterTranserClass<PollTranser> RegisterWebsocket("polling");
PollTranser::PollTranser()
{
}


PollTranser::~PollTranser()
{
}

void PollTranser::onRequest(Request& req, Response& res)
{
	if (HTTP_GET == req.method_) {
		this->onPollRequest(req, res);
	}
	else if (HTTP_POST == req.method_) {
		this->onDataRequest(req, res);
	}
	else {
		res.send(Response::internal_server_error);
	}
}

void PollTranser::onPollRequest(Request& req, Response& res)
{
	transback = &res;
	//throw std::exception("The method or operation is not implemented.");
}

void PollTranser::onDataRequest(Request& req, Response& res)
{
	LOG(debug) << "data " << req.body_;
	shared_ptr<EngineIoParser::PackageVector> paVec=EngineIoParser::decodePayload(req.body_);
	foreach (EngineIoParser::PackagePtr paPtr,*paVec)
	{
		onPacket(*paPtr);
	}
	res.setHeader("Content-Type", "text/html"); 
	res.setStatus(Response::ok);
	res.sendData(std::string("ok"));
}

void PollTranser::onPacket(EngineIoParser::Package &pa)
{
/*	if ('open' == this.readyState) {
		// export packet event
		debug('packet');
		this.emit('packet', packet);

		// Reset ping timeout on any packet, incoming data is a good sign of
		// other side's liveness
		this.setPingTimeout();

		switch (packet.type) {

		case 'ping':
			debug('got ping');
			this.sendPacket('pong');
			this.emit('heartbeat');
			break;

		case 'error':
			this.onClose('parse error');
			break;

		case 'message':
			this.emit('data', packet.data);
			this.emit('message', packet.data);
			break;
		}
	}
	else {
		debug('packet received with closed socket');
	}*/
}
