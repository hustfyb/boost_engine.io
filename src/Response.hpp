//
// reply.hpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <iostream>
#include <boost/enable_shared_from_this.hpp>
#include "header.hpp"
#include "Request.hpp"
using namespace boost::asio;
/// A reply to be sent to a client.
class Response :boost::asio::coroutine
	, public boost::enable_shared_from_this<Response>
{
public:
	Response(shared_ptr<tcp::socket> sock) {
		socket_ = sock;
		status = Response::ok;
	};
	~Response() {}
	/// The status of the reply.
	enum status_type
	{
		ok = 200,
		created = 201,
		accepted = 202,
		no_content = 204,
		multiple_choices = 300,
		moved_permanently = 301,
		moved_temporarily = 302,
		not_modified = 304,
		bad_request = 400,
		unauthorized = 401,
		forbidden = 403,
		not_found = 404,
		internal_server_error = 500,
		not_implemented = 501,
		bad_gateway = 502,
		service_unavailable = 503
	} status;

	/// The headers to be included in the reply.
	std::map<std::string,std::string> headers;

	/// The content to be sent in the reply.
	std::string content;

	/// Convert the reply into a vector of buffers. The buffers do not own the
	/// underlying memory blocks, therefore the reply object must remain valid and
	/// not be changed until the write operation has completed.
	std::vector<boost::asio::const_buffer> to_buffers();

	void send(status_type status);
	void rawSend(const char *data, int size, Callback cb);
	void sendData(std::string &data);
	shared_ptr<tcp::socket> getSocket();
	void sendData(const char *data);
	void sendHead(boost::function<void(system::error_code, std::size_t)> cb);
	void sendDataContinue(char *data, int dataSize, function<void(system::error_code, std::size_t)> cb);
	void sendFile(std::string &docRoot, std::string &url, function<void(system::error_code, std::size_t)> cb);
	void setHeader(std::string &name, std::string &value);
	void setHeader(const char* name, const char * value);
	void setStatus(enum status_type status);
	void setCross(RequestPtr request);
	void end(Callback cb);
	void clear();
	void defaultHandler(system::error_code);
private:
	char buff[4096];
	/// ¶Ô¶ËµÄsocket;
	shared_ptr<tcp::socket> socket_;
	bool url_decode(const std::string& in, std::string& out);
};

typedef shared_ptr<Response> ResponsePtr;