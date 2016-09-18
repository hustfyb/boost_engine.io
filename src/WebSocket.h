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
	int headDone_;
	int dataStart;
	char mask_[4];
	long long dataLen_;
	std::string data_;
	void encodeData(std::string &content, std::string & data);
};
class WebSocket;
typedef shared_ptr<WebSocket> WebSocketPtr;
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
	static signals2::signal<void(WebSocketPtr)> sigConnect;
	signals2::signal<void(WebSocketPtr)> sigMessage;
	signals2::signal<void(WebSocketPtr)> sigClose;
	RequestPtr req_;
	ResponsePtr res_;
	WebsocketDataParser wParser_;
	void sendData(std::string & data);
private:
	void doWebSocket(system::error_code ec,size_t size);
	boost::tribool getData(unsigned char *data, size_t length);
	Callback cb_;
	typedef array<unsigned char, 8192> ArrayBuffer;
	shared_ptr<ArrayBuffer> buffer_;
	shared_ptr<tcp::socket> socket_;
	std::string data_;
	std::string reply_;
	bool processData();
	void sendPong();
	void encodeData(std::string &content, std::string &data);
	void sendHandler(system::error_code, size_t length);
	std::string message_;
};
