#pragma once
#include "TranserBase.hpp"
#include "Response.hpp"
#include "EngineSocket.hpp"
#include "EngineIoParser.hpp"
class PollTranser :public TranserBase
{
public:
	PollTranser();
	~PollTranser();
	Response *transback;
	virtual	void onRequest(RequestPtr request, ResponsePtr response);

	void onPollRequest(RequestPtr req, ResponsePtr res);
	void onDataRequest(RequestPtr req, ResponsePtr res);
private:
	void onPacket(EngineIoParser::Package &);
};

