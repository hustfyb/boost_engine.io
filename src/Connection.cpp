#include "header.hpp"
#include "Connection.h"
#include "SocketIo.hpp"
#include "Server.hpp"
#include "Setting.hpp"
#include <boost/xpressive/xpressive.hpp>

#define CallFromThis(x) bind(x, shared_from_this(), _1, _2) 
using namespace xpressive;

Connection::Connection(Server &serv)
	:server(serv)
	,ios(serv.get_io_service())
	,m_socket(serv.get_io_service())
	,response(m_socket)
{
	logf << "\r\n";
}


Connection::~Connection()
{
	logf << "\r\n";
}

#include <boost/asio/yield.hpp>
void Connection::run(system::error_code ec, std::size_t length)
{
	tribool parseResult = false;
	bool exit = false;
	bool bit = false;
	cregex regex;
	reenter(this) {
		if (!ec) {
			buffer_.reset(new ArrayBuffer);
			while (!exit)
			{
				do {
					yield m_socket.async_read_some(boost::asio::buffer(*buffer_), bind(&Connection::run, shared_from_this(), _1, _2));
					if (length == 0) {
						exit = true;
						break;
					}
					//std::cout << parser->state << "\r\n";
					parseResult = request.parse(buffer_->data(), length);
				} while (indeterminate(parseResult));
				if (parseResult == true) {
					filter_iter = server.filterMap.begin();
					while (filter_iter !=server.filterMap.end())
					{
						regex = cregex::compile(filter_iter->first);
						if (regex_match(request.url.c_str(), regex)) {
							yield filter_iter->second->process(request, response, CallFromThis(&Connection::run));
							filterMatch = true;
						}
						filter_iter++;
					}


					//yield parseResult = server.processFilter(request, response, bind(&Connection::run, shared_from_this(), _1, _2));
					if (!filterMatch) {
						yield response.sendFile(g_setting.getRoot(), request.url, bind(&Connection::run, shared_from_this(), _1, _2));
					}
					//socket.io Test
// 					if (request.upgrade()) {
// 						logf << "upgrade\r\n";
// 					}
// 					else{
// 						bit =SocketIo::match(request, response,bind(&Connection::run, shared_from_this(), _1, _2));
// 						if (!bit) {
// 						
// 						}
// 						else {
// 							yield;
// 						}
						//yield response.send(Response::bad_request, bind(&ClientHandler::run, shared_from_this(), _1, _2));
						//yield	response.send(m_docRoot, request.url, bind(&ClientHandler::run, shared_from_this(), _1, _2));
					//}
				}
			}
			//m_socket.shutdown(tcp::socket::shutdown_both, ec);
		}
		else {
			logf << ec;
		}
		m_socket.shutdown(tcp::socket::shutdown_both, ec);
		logf << "client down\r\n";
	}
}
#include <boost/asio/unyield.hpp>
