#include "header.hpp"
#include "PollTranser.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "engineIoParser.hpp"
std::vector<std::string> TranserBase::names;
RegisterTranserClass<PollTranser> RegisterWebsocket("polling");
PollTranser::PollTranser()
{
}


PollTranser::~PollTranser()
{
}

void PollTranser::onRequest(Request& req, Response& res, Callback cb)
{
	if (HTTP_GET == req.method_) {
		this->onPollRequest(req, res, cb);
	}
	else if (HTTP_POST == req.method_) {
		this->onDataRequest(req, res, cb);
	}
	else {
		res.send(Response::internal_server_error,cb);
	}
}

void PollTranser::onPollRequest(Request& req, Response& res, Callback cb)
{
	cb(system::error_code(), 0);
	transback = &res;
	//throw std::exception("The method or operation is not implemented.");
}

void PollTranser::onDataRequest(Request& req, Response& res, Callback cb)
{
	LOG(debug) << "data " << req.body_;
	engineIoParser::decodePayload(req.body_);
	res.setHeader("Content-Type", "text/html"); 
	res.setStatus(Response::ok);
	res.sendData(std::string("ok"), cb);
}
