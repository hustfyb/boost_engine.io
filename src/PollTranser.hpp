#pragma once
#include "TranserBase.hpp"
#include "Response.hpp"
#include "EngineIoParser.hpp"
class PollTranser :public TranserBase
{
public:
	PollTranser();
	~PollTranser();
	Response *transback;
	virtual	void onRequest(Request& request, Response& response);

	void onPollRequest(Request& req, Response& res);
	void onDataRequest(Request& req, Response& res);
private:
	void onPacket(EngineIoParser::Package &);
};

