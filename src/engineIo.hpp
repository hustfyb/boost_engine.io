#pragma once
#include "header.hpp"
#include "Server.hpp"
#include "FilterBase.hpp"
class EngineIo: public FilterBase
{
public:
	EngineIo();
	virtual void process(Request&, Response&, Callback);

//configValue
	int pingInterval;
	int pingTimeout;
private:
	void handleHandShake(Request& request, Response& response, Callback cb);
};

