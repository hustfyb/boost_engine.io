//
// server.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include "header.hpp"
#include "ClientHandler.h"
//#include "request_parser.hpp"

namespace httpServer {

//	struct Request;
//	class Response;
	class Server:asio::coroutine
	{
	public:
		/// Construct the server to listen on the specified TCP address and port, and
		/// serve up files from the given directory.
		explicit Server(boost::asio::io_service& io_service,
			const std::string& address, const std::string& port);
// 		/// Perform work associated with the server.
// 		void operator()(
// 			boost::system::error_code ec = boost::system::error_code(),
// 			std::size_t length = 0);

		void startListen(system::error_code ec);
	private:
		shared_ptr<ClientHandler> m_clientHandler;

		void step(system::error_code ec, std::size_t length);

		typedef boost::asio::ip::tcp tcp;

// 		boost::function<void(const Request&, Response &)>  file_handler_;
// 		boost::function<bool(shared_ptr<Request>, shared_ptr<Response>)> request_handler_;

// 		asio::coroutine  accepterCo;
// 		asio::coroutine  clientHandlerCo;
		asio::io_service &ios;
		/// Acceptor used to listen for incoming connections.
		boost::shared_ptr<tcp::acceptor> m_acceptor;

 		/// The current connection from a client.
 		boost::shared_ptr<tcp::socket> m_clientSocket;
// 
// 		/// Buffer for incoming data.
// 		boost::shared_ptr<boost::array<char, 8192> > buffer_;
// 
// 		/// The incoming request.
// 		boost::shared_ptr<Request> request_;
// 
// 		/// Whether the request is valid or not.
// 		boost::tribool valid_request_;
// 
// 		/// The parser for the incoming request.
// 		request_parser request_parser_;
// 
// 		/// The reply to be sent back to the client.
// 		boost::shared_ptr<Response> reply_;

	};

} // namespace httpServer
