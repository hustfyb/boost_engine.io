#pragma once
#include "header.hpp"
#include "Server.hpp"
#include "FilterBase.hpp"
class EngineIo: public FilterBase
{
public:
	EngineIo();
	void sendErrorMessage(Request&request, Response&response, int code,Callback cb);
	int verify(Request&request, Response&response);
	virtual void process(Request&, Response&, Callback);

//configValue
	int pingInterval;
	int pingTimeout;

	typedef enum 
	{
		ERROR_OK = -1,
		UNKNOWN_TRANSPORT= 0,
		UNKNOWN_SID,
		BAD_HANDSHAKE_METHOD ,
		BAD_REQUEST 
	}Errors;
	char *errorMessages[4] = {
		"Transport unknown",
		"Session ID unknown",
		"Bad handshake method",
		"Bad request"
	};
private:
	void handleHandShake(Request& request, Response& response, Callback cb);
};

