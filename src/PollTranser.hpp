#pragma once
#include "TranserBase.hpp"
#include "Response.hpp"
class PollTranser :public TranserBase
{
public:
	PollTranser();
	~PollTranser();
	Response *transback;
	virtual	void onRequest(Request& request, Response& response, Callback cb);

	void onPollRequest(Request& req, Response& res, Callback cb);
	void onDataRequest(Request& req, Response& res, Callback cb);
};

