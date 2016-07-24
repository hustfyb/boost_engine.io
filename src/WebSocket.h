#pragma once
#include "header.hpp"
#include "Request.hpp"
#include "Response.hpp"
class WebSocket:
	asio::coroutine
{
public:
	WebSocket();
	~WebSocket();
	void process(RequestPtr req, ResponsePtr resp, Callback cb);
private:
	void doWebSocket(system::error_code ec,size_t size);
	RequestPtr req_;
	ResponsePtr res_;
	Callback cb_;
	typedef array<char, 8192> ArrayBuffer;
	shared_ptr<ArrayBuffer> buffer_;
};
typedef shared_ptr<WebSocket> WebSocketPtr;