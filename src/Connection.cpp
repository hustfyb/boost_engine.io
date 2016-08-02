#include "header.hpp"
#include "Connection.hpp"
#include "Server.hpp"
#include "Setting.hpp"
#include <boost/xpressive/xpressive.hpp>
#include "util.hpp"

#define CallFromThis(x) bind(x, shared_from_this(), _1, _2) 
using namespace xpressive;

Connection::Connection(Server &serv)
	:server(serv)
	,ios(serv.get_io_service())
{
	socket_ = make_shared<tcp::socket>(serv.get_io_service());
	request_ = make_shared<Request>();
	response_ = make_shared<Response>(socket_);
}



Connection::~Connection()
{
	LOG(info) << "Connection down" << request_->url;
}



#include <boost/asio/yield.hpp>
void Connection::run(system::error_code ec, std::size_t length)
{
	tribool parseResult = false;
	bool exit = false;
	bool bit = false;
	cregex regex;
	reenter(this)
	{
		if (!ec)
		{
			buffer_.reset(new ArrayBuffer);
			while (!exit)
			{
				do {
					yield socket_->async_read_some(boost::asio::buffer(*buffer_), CallFromThis(&Connection::run));
					if (length == 0) {
						exit = true;
						break;
					}
					request_->data_ += buffer_->data();
					parseResult = request_->parse(buffer_->data(), length);
				} while (indeterminate(parseResult));
				if (parseResult == true)
				{
					LOG(debug) << request_->url;
					if ((MapGet(request_->header_, "Connection", "")) == "Upgrade")
					{	//WebSocket
						ws_ = make_shared<WebSocket>();
						yield ws_->process(request_, response_, CallFromThis(&Connection::run));
					}
					else
					{
						if (!server.processFilter(request_, response_))
						{
							response_->sendFile(g_setting.getRoot(), request_->url, CallFromThis(&Connection::run));
						}
						yield response_->end(CallFromThis(&Connection::run));
					}
					request_ = make_shared<Request>();
					response_ = make_shared<Response>(socket_);
				}
			}
		}
		else {
			logf << ec;
		}
	}
}
#include <boost/asio/unyield.hpp>
