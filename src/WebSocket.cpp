#include "header.hpp"
#include "WebSocket.h"
#include "../submodules/c-websocket/include/cWebSockets.h"

WebSocket::WebSocket()
{
}


WebSocket::~WebSocket()
{
}

void WebSocket::process(RequestPtr req, ResponsePtr res, Callback cb)
{
	req_ = req;
	res_ = res;
	cb_ = cb;
}
#define CallFromThis(x) bind(x, shared_from_this(), _1, _2) 
#include <boost/asio/yield.hpp>
void WebSocket::doWebSocket(system::error_code ec, size_t size)
{
	reenter(this)
	{
		//handshake
		buffer_.reset(new ArrayBuffer);
		WEBSOCKET_generate_handshake(req_->data_.c_str(), buffer_->data(), buffer_->size());
//		res_->send(buffer_->data());
		//yield res_->end(CallFromThis(&WebSocket::doWebSocket));
		if (!ec)
		{
		}
		else 
		{
			LOG(error)<< ec;
		}
		return cb_(system::error_code(), 0);
	}

}
#include <boost/asio/unyield.hpp>
