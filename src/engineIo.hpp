#pragma once
#include "header.hpp"
#include "Server.hpp"
#include "FilterBase.hpp"

class EngineIo: public FilterBase
{
public:
	typedef enum
	{
		open = 0
		, close    // non-ws
		, ping
		, pong
		, message
		, upgrade
		, noop
	}EngineIoType;

	EngineIo(asio::io_service& );
	void sendErrorMessage(RequestPtr request, ResponsePtr response, int code);
	int verify(Request &, Response &);
	virtual void process(RequestPtr, ResponsePtr);

//configValue
	int pingInterval_;
	int pingTimeout_;

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
	void handleHandShake(RequestPtr request, ResponsePtr response);
	asio::io_service &ios_;
};

