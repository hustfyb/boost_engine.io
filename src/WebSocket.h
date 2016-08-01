#pragma once
#include "header.hpp"
#include "Request.hpp"
#include "Response.hpp"

class WebsocketDataParser : asio::coroutine
{
public:
	typedef struct
	{
		unsigned char opcode : 4;
		unsigned char rsv : 3;
		unsigned char fin : 1;
		unsigned char pLen : 7;
		unsigned char mask : 1;
	}Head;
	Head head;
	boost::tuple<boost::tribool, int> parse(unsigned char *data, int length);

	void clear();
	int parserStage_;
	int dataStart;
	char mask_[4];
	long long dataLen_;
	char msg_[64 * 1024];
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
	char *data;
private:
	void doWebSocket(system::error_code ec,size_t size);
	boost::tribool getData(unsigned char *data, size_t length);
	RequestPtr req_;
	ResponsePtr res_;
	Callback cb_;
	typedef array<unsigned char, 8192> ArrayBuffer;
	shared_ptr<ArrayBuffer> buffer_;
	shared_ptr<tcp::socket> socket_;
	std::string data_;
	std::string reply_;
	WebsocketDataParser wParser_;
};
typedef shared_ptr<WebSocket> WebSocketPtr;