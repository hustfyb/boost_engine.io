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
	ResponsePtr dataRes_;
	RequestPtr dataReq_;
	virtual void init(RequestPtr request, ResponsePtr response);
	virtual	void onRequest(RequestPtr request, ResponsePtr response);
	virtual void sendPacket(int type, std::string &data);

private:
	void onPollRequest(RequestPtr req, ResponsePtr res);
	void onDataRequest(RequestPtr req, ResponsePtr res);
	void onPacket(EngineIoParser::Packet &);
};

