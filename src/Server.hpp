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
#include "Connection.hpp"
#include "FilterBase.hpp"
typedef std::map<std::string, FilterBase *> FilterMap;

class Server :asio::coroutine
{
	friend class Connection;
public:
	explicit Server(asio::io_service& io_service);
	asio::io_service &get_io_service() {
		return ios;
	}

	void startListen(system::error_code ec);
	void addFilter(char *match, FilterBase &filter);
	bool processFilter(shared_ptr<Request> req, shared_ptr<Response> res);
private:
	asio::io_service &ios;
	shared_ptr<tcp::acceptor> m_acceptor;
	shared_ptr<Connection> m_connection;
	FilterMap filterMap;
};

