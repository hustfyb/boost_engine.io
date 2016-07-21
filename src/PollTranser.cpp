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

void PollTranser::init(RequestPtr request, ResponsePtr response)
{
	dataReq_ = request;
	dataRes_ = response;
}

void PollTranser::onRequest(RequestPtr req, ResponsePtr res)
{
	if (HTTP_GET == req->method_) {
		this->onPollRequest(req, res);
	}
	else if (HTTP_POST == req->method_) {
		this->onDataRequest(req, res);
	}
	else {
		res->send(Response::internal_server_error);
	}
}

void PollTranser::sendPacket(int type, std::string &data)
{
	std::string payload = EngineIoParser::encodePayloadAsBinary(EngineIoParser::encodePacket(type,data));
	dataRes_->setHeader(std::string("Content-Type"), std::string("application/octet-stream"));
	dataRes_->setCross(dataReq_);
	dataRes_->sendData(payload);
	dataRes_->end(NULL);
	LOG(info) << dataRes_ <<":"<< data;
}

void PollTranser::onPollRequest(RequestPtr req, ResponsePtr res)
{
	dataReq_ = req;
	dataRes_ = res;
	LOG(debug) << "save " << req->url << ":" << dataRes_;
}

void PollTranser::onDataRequest(RequestPtr req, ResponsePtr res)
{
	LOG(debug) << "data " << req->body_;
	shared_ptr<EngineIoParser::PacketVector> paVec=EngineIoParser::decodePayload(req->body_);
	foreach (EngineIoParser::PacketPtr paPtr,*paVec)
	{
		engineSocket_->onPacket(paPtr);
	}
	res->setHeader("Content-Type", "text/html"); 
	res->setCross(req);
	res->setStatus(Response::ok);
	res->sendData(std::string("ok"));
}