#include "header.hpp"
#include "WebSocket.h"
extern "C"
{
#include "../submodules/c-websocket/cWebSockets.h"
}

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
	socket_ = res->getSocket();
	doWebSocket(system::error_code(), 0);
}

#define CallFromThis(x) bind(&x, shared_from_this(), _1, _2) 


#include <boost/asio/yield.hpp>
void WebSocket::doWebSocket(system::error_code ec, size_t size)
{
	char tempData[8192];
	if (!ec)
	{
		reenter(this)
		{
			//handshake
			buffer_.reset(new ArrayBuffer);
			WEBSOCKET_generate_handshake(req_->data_.c_str(), buffer_->data(), buffer_->size());
			
			yield socket_->async_send(buffer(*buffer_,strlen(buffer_->data())),CallFromThis(WebSocket::doWebSocket));
			//open

			while (true)
			{
				yield socket_->async_read_some(buffer(*buffer_), CallFromThis(WebSocket::doWebSocket));
				rt = WEBSOCKET_get_content(buffer_->data, size, tempData, sizeof(tempData));

			}
			return cb_(system::error_code(), 0);
		}
	}
	else
	{
		LOG(error) << ec;
	}

}
#include <boost/asio/unyield.hpp>
