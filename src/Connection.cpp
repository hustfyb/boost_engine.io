#include "header.hpp"
#include "Connection.hpp"
#include "Server.hpp"
#include "Setting.hpp"
#include <boost/xpressive/xpressive.hpp>

#define CallFromThis(x) bind(x, shared_from_this(), _1, _2) 
using namespace xpressive;

Connection::Connection(Server &serv)
	:server(serv)
	,ios(serv.get_io_service())
	,m_socket(serv.get_io_service())
{
	request_ = make_shared<Request>();
	response_ = make_shared<Response>(m_socket);
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
					yield m_socket.async_read_some(boost::asio::buffer(*buffer_), CallFromThis(&Connection::run));
					if (length == 0) {
						exit = true;
						break;
					}
					parseResult = request_->parse(buffer_->data(), length);
				} while (indeterminate(parseResult));
				if (parseResult == true)
				{
					if (!server.processFilter(request_,response_))
					{
						response_->sendFile(g_setting.getRoot(), request_->url, CallFromThis(&Connection::run));
					}
					yield response_->end(CallFromThis(&Connection::run));
					response_->clear();
				}
			}
		}
		else {
			logf << ec;
		}
		m_socket.shutdown(tcp::socket::shutdown_both, ec);
		logf << "client down\r\n";
	}
}

//void Connection::recvData(system::error_code ec, std::size_t length)
//{
//	tribool parseResult = false;
//	bool exit = false;
//	bool bit = false;
//	cregex regex;
//	reenter(this)
//	{
//		if (!ec)
//		{
//			buffer_.reset(new ArrayBuffer);
//			do {
//				yield m_socket.async_read_some(boost::asio::buffer(*buffer_), CallFromThis(&Connection::recvData));
//				if (length == 0)
//				{
//					exit = true;
//					break;
//				}
//				parseResult = request.parse(buffer_->data(), length);
//			} while (indeterminate(parseResult));
//			if (parseResult == true)
//			{
//				filter_iter = server.filterMap.begin();
//				while (filter_iter != server.filterMap.end())
//				{
//					regex = cregex::compile(filter_iter->first);
//					if (regex_match(request.url.c_str(), regex))
//					{
//						yield filter_iter->second->process(request, response, CallFromThis(&Connection::run));
//						filterMatch = true;
//					}
//					filter_iter++;
//				}
//				if (!filterMatch) {
//					yield response.sendFile(g_setting.getRoot(), request.url, bind(&Connection::run, shared_from_this(), _1, _2));
//				}
//			}
//			//m_socket.shutdown(tcp::socket::shutdown_both, ec);
//		}
//		else {
//			logf << ec;
//		}
//		m_socket.shutdown(tcp::socket::shutdown_both, ec);
//		logf << "client down\r\n";
//	}
//}

#include <boost/asio/unyield.hpp>
