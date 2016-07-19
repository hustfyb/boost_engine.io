#pragma once
#include "header.hpp"
#include "Server.hpp"
#include "FilterBase.hpp"
#include "EngineSocket.hpp"

typedef struct {
	std::string sid;
	shared_ptr<EngineSocket> socket;
	int state; /* -2:disconnected; -1:disconnecting; 0:connecting; 1:connected; */
			   //	ev_timer close_timeout;

} EngineIoClient;

class EngineIo: public FilterBase
{
public:
	EngineIo();
	void sendErrorMessage(RequestPtr request, ResponsePtr response, int code);
	int verify(Request &, Response &);
	virtual void process(RequestPtr, ResponsePtr);

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
	void handleHandShake(RequestPtr request, ResponsePtr response);
};

