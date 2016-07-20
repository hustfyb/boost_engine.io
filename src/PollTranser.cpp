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

void PollTranser::onPollRequest(RequestPtr req, ResponsePtr res)
{
	//transback = res;
	throw std::exception("The method or operation is not implemented.");
}

void PollTranser::onDataRequest(RequestPtr req, ResponsePtr res)
{
	LOG(debug) << "data " << req->body_;
	shared_ptr<EngineIoParser::PackageVector> paVec=EngineIoParser::decodePayload(req->body_);
	foreach (EngineIoParser::PackagePtr paPtr,*paVec)
	{
		engineSocket_->onPacket(paPtr);
	}
	res->setHeader("Content-Type", "text/html"); 
	res->setStatus(Response::ok);
	res->sendData(std::string("ok"));
}