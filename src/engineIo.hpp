#pragma once
#include "header.hpp"
#include "Server.hpp"
#include "FilterBase.hpp"
#include "WebSocket.h"
class EngineIo : public FilterBase, public enable_shared_from_this<EngineIo>
{
public:
	EngineIo(asio::io_service& );
	int verify(RequestPtr);
	virtual void process(RequestPtr, ResponsePtr);
//configValue
	int pingInterval_;
	int pingTimeout_;

	void attach(shared_ptr<Server> httpServer);
public:
	void removeSocket(std::string &id);
	void wsOnConnect(WebSocketPtr);
private:
	char *errorMessages[4] = {
		"Transport unknown",
		"Session ID unknown",
		"Bad handshake method",
		"Bad request"
	};
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
	typedef enum
	{
		ERROR_OK = -1,
		UNKNOWN_TRANSPORT = 0,
		UNKNOWN_SID,
		BAD_HANDSHAKE_METHOD,
		BAD_REQUEST
	}Errors;
	void handleHandShake(RequestPtr request, ResponsePtr response);
	void sendErrorMessage(RequestPtr request, ResponsePtr response, int code);
	asio::io_service &ios_;
};

