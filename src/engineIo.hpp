#pragma once
#include "header.hpp"
#include "Server.hpp"
class engineIo
{
public:
	engineIo();
	void operator()(Request&, Response&, Callback);

//configValue
	int pingInterval;
	int pingTimeout;
private:
	void handleHandShake(Request& request, Response& response, Callback cb);
};

