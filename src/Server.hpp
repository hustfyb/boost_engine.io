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
#include "Connection.h"
typedef function<void(system::error_code ec, std::size_t length)> Callback;
class Server :asio::coroutine
{
public:
	explicit Server(asio::io_service& io_service);
	asio::io_service &get_io_service() {
		return ios;
	}

	void startListen(system::error_code ec);
	void addFilter(char *filter, function<void(Request&, Response&, Callback)>);

private:
	asio::io_service &ios;
	shared_ptr<tcp::acceptor> m_acceptor;
	shared_ptr<Connection> m_connection;
	typedef std::map<std::string, ProductCreator> AssocMap;

};

