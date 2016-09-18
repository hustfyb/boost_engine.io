#pragma once
#include "TranserBase.hpp"
#include "WebSocket.h"
#include "EngineSocket.hpp"

class WebsocketTranser:public TranserBase
{
public:
	WebsocketTranser();
	~WebsocketTranser();
	virtual void init(RequestPtr request, ResponsePtr response) {};
	virtual void onRequest(RequestPtr request, ResponsePtr response) {};
	virtual void sendPacket(int type, std::string &data) ;
	void setHandler(WebSocketPtr);
	void onMessage(WebSocketPtr ws);
private:
	WebSocketPtr ws_;
};

