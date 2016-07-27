#pragma once
#include "header.hpp"
#include "Request.hpp"
#include "Response.hpp"

class WebsocketDataParser : asio::coroutine
{
public:
	typedef struct
	{
		char fin : 1;
		char rsv : 3;
		char opcode : 4;
		char mask : 1;
		char pLen : 7;
	}Head;
	Head head;
	boost::tuple<boost::tribool, int> parse(char *data, int length);

	void clear();
	int parserStage_;
};

class WebSocket:
	asio::coroutine,
	public enable_shared_from_this<WebSocket>
{
public:
	WebSocket();
	~WebSocket();
	void process(RequestPtr req, ResponsePtr resp, Callback cb);
	int generateHandshake(RequestPtr req, std::string &reply);
private:
	void doWebSocket(system::error_code ec,size_t size);
	boost::tribool getData(char *data, size_t length);
	RequestPtr req_;
	ResponsePtr res_;
	Callback cb_;
	typedef array<char, 8192> ArrayBuffer;
	shared_ptr<ArrayBuffer> buffer_;
	shared_ptr<tcp::socket> socket_;
	std::string data_;
	std::string reply_;
	WebsocketDataParser wParser_;
};
typedef shared_ptr<WebSocket> WebSocketPtr;