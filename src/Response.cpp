//
// reply.cpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include "header.hpp"
#include "Response.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>
#include <fstream>
#include "Request.hpp"
#include "mime_types.hpp"
namespace status_strings {

	const std::string ok =
		"HTTP/1.1 200 OK\r\n";
	const std::string created =
		"HTTP/1.1 201 Created\r\n";
	const std::string accepted =
		"HTTP/1.1 202 Accepted\r\n";
	const std::string no_content =
		"HTTP/1.1 204 No Content\r\n";
	const std::string multiple_choices =
		"HTTP/1.1 300 Multiple Choices\r\n";
	const std::string moved_permanently =
		"HTTP/1.1 301 Moved Permanently\r\n";
	const std::string moved_temporarily =
		"HTTP/1.1 302 Moved Temporarily\r\n";
	const std::string not_modified =
		"HTTP/1.1 304 Not Modified\r\n";
	const std::string bad_request =
		"HTTP/1.1 400 Bad Request\r\n";
	const std::string unauthorized =
		"HTTP/1.1 401 Unauthorized\r\n";
	const std::string forbidden =
		"HTTP/1.1 403 Forbidden\r\n";
	const std::string not_found =
		"HTTP/1.1 404 Not Found\r\n";
	const std::string internal_server_error =
		"HTTP/1.1 500 Internal Server Error\r\n";
	const std::string not_implemented =
		"HTTP/1.1 501 Not Implemented\r\n";
	const std::string bad_gateway =
		"HTTP/1.1 502 Bad Gateway\r\n";
	const std::string service_unavailable =
		"HTTP/1.1 503 Service Unavailable\r\n";

	boost::asio::const_buffer to_buffer(Response::status_type status)
	{
		switch (status)
		{
		case Response::ok:
			return boost::asio::buffer(ok);
		case Response::created:
			return boost::asio::buffer(created);
		case Response::accepted:
			return boost::asio::buffer(accepted);
		case Response::no_content:
			return boost::asio::buffer(no_content);
		case Response::multiple_choices:
			return boost::asio::buffer(multiple_choices);
		case Response::moved_permanently:
			return boost::asio::buffer(moved_permanently);
		case Response::moved_temporarily:
			return boost::asio::buffer(moved_temporarily);
		case Response::not_modified:
			return boost::asio::buffer(not_modified);
		case Response::bad_request:
			return boost::asio::buffer(bad_request);
		case Response::unauthorized:
			return boost::asio::buffer(unauthorized);
		case Response::forbidden:
			return boost::asio::buffer(forbidden);
		case Response::not_found:
			return boost::asio::buffer(not_found);
		case Response::internal_server_error:
			return boost::asio::buffer(internal_server_error);
		case Response::not_implemented:
			return boost::asio::buffer(not_implemented);
		case Response::bad_gateway:
			return boost::asio::buffer(bad_gateway);
		case Response::service_unavailable:
			return boost::asio::buffer(service_unavailable);
		default:
			return boost::asio::buffer(internal_server_error);
		}
	}

} // namespace status_strings

namespace misc_strings {

	const char name_value_separator[] = { ':', ' ' };
	const char crlf[] = { '\r', '\n' };

} // namespace misc_strings
  
std::vector<boost::asio::const_buffer> Response::to_buffers()
{
 	std::vector<boost::asio::const_buffer> buffers;
 	buffers.push_back(status_strings::to_buffer(status));
	for (auto header = headers.begin(); header != headers.end(); header++) {
  		buffers.push_back(boost::asio::buffer(header->first));
 		buffers.push_back(boost::asio::buffer(misc_strings::name_value_separator));
  		buffers.push_back(boost::asio::buffer(header->second));
  		buffers.push_back(boost::asio::buffer(misc_strings::crlf));
 	}
 	buffers.push_back(boost::asio::buffer(misc_strings::crlf));
 	buffers.push_back(boost::asio::buffer(content));
	return buffers;
}

namespace stock_replies {

	const char ok[] = "";
	const char created[] =
		"<html>"
		"<head><title>Created</title></head>"
		"<body><h1>201 Created</h1></body>"
		"</html>";
	const char accepted[] =
		"<html>"
		"<head><title>Accepted</title></head>"
		"<body><h1>202 Accepted</h1></body>"
		"</html>";
	const char no_content[] =
		"<html>"
		"<head><title>No Content</title></head>"
		"<body><h1>204 Content</h1></body>"
		"</html>";
	const char multiple_choices[] =
		"<html>"
		"<head><title>Multiple Choices</title></head>"
		"<body><h1>300 Multiple Choices</h1></body>"
		"</html>";
	const char moved_permanently[] =
		"<html>"
		"<head><title>Moved Permanently</title></head>"
		"<body><h1>301 Moved Permanently</h1></body>"
		"</html>";
	const char moved_temporarily[] =
		"<html>"
		"<head><title>Moved Temporarily</title></head>"
		"<body><h1>302 Moved Temporarily</h1></body>"
		"</html>";
	const char not_modified[] =
		"<html>"
		"<head><title>Not Modified</title></head>"
		"<body><h1>304 Not Modified</h1></body>"
		"</html>";
	const char bad_request[] =
		"<html>"
		"<head><title>Bad Request</title></head>"
		"<body><h1>400 Bad Request</h1></body>"
		"</html>";
	const char unauthorized[] =
		"<html>"
		"<head><title>Unauthorized</title></head>"
		"<body><h1>401 Unauthorized</h1></body>"
		"</html>";
	const char forbidden[] =
		"<html>"
		"<head><title>Forbidden</title></head>"
		"<body><h1>403 Forbidden</h1></body>"
		"</html>";
	const char not_found[] =
		"<html>"
		"<head><title>Not Found</title></head>"
		"<body><h1>404 Not Found</h1></body>"
		"</html>";
	const char internal_server_error[] =
		"<html>"
		"<head><title>Internal Server Error</title></head>"
		"<body><h1>500 Internal Server Error</h1></body>"
		"</html>";
	const char not_implemented[] =
		"<html>"
		"<head><title>Not Implemented</title></head>"
		"<body><h1>501 Not Implemented</h1></body>"
		"</html>";
	const char bad_gateway[] =
		"<html>"
		"<head><title>Bad Gateway</title></head>"
		"<body><h1>502 Bad Gateway</h1></body>"
		"</html>";
	const char service_unavailable[] =
		"<html>"
		"<head><title>Service Unavailable</title></head>"
		"<body><h1>503 Service Unavailable</h1></body>"
		"</html>";

	std::string to_string(Response::status_type status)
	{
		switch (status)
		{
		case Response::ok:
			return ok;
		case Response::created:
			return created;
		case Response::accepted:
			return accepted;
		case Response::no_content:
			return no_content;
		case Response::multiple_choices:
			return multiple_choices;
		case Response::moved_permanently:
			return moved_permanently;
		case Response::moved_temporarily:
			return moved_temporarily;
		case Response::not_modified:
			return not_modified;
		case Response::bad_request:
			return bad_request;
		case Response::unauthorized:
			return unauthorized;
		case Response::forbidden:
			return forbidden;
		case Response::not_found:
			return not_found;
		case Response::internal_server_error:
			return internal_server_error;
		case Response::not_implemented:
			return not_implemented;
		case Response::bad_gateway:
			return bad_gateway;
		case Response::service_unavailable:
			return service_unavailable;
		default:
			return internal_server_error;
		}
	}
} // namespace stock_replies

void Response::send(status_type status)
{
	setStatus(status);
	sendData("");
}
void Response::sendData(const char *data) {
	sendData(std::string(data));
};

void Response::sendData(std::string &data)
{
	content += data;
}

void Response::sendHead(boost::function<void(boost::system::error_code, std::size_t)> cb)
{
	socket_.async_send(this->to_buffers(), cb);
}

void Response::sendDataContinue(char *data, int dataSize, function<void(system::error_code, std::size_t)> cb)
{
	content.clear();
	content.append(data, dataSize);
	asio::async_write(socket_, asio::buffer(content), cb);
}

bool Response::url_decode(const std::string& in, std::string& out)
{
	out.clear();
	out.reserve(in.size());
	for (std::size_t i = 0; i < in.size(); ++i)
	{
		if (in[i] == '%')
		{
			if (i + 3 <= in.size())
			{
				int value = 0;
				std::istringstream is(in.substr(i + 1, 2));
				if (is >> std::hex >> value)
				{
					out += static_cast<char>(value);
					i += 2;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else if (in[i] == '+')
		{
			out += ' ';
		}
		else if (in[i] == '?') {
			break;
		}
		else
		{
			out += in[i];
		}
	}
	return true;
}

void Response::sendFile(std::string &docRoot, std::string &url, function<void(system::error_code, std::size_t)> cb)
{
	std::string request_path;
	if (!url_decode(url, request_path))
	{
		this->send(Response::bad_request);
		return;
	}
	// Request path must be absolute and not contain "..".
	if (request_path.empty() || request_path[0] != '/'
		|| request_path.find("..") != std::string::npos)
	{
		this->send(Response::bad_request);
		return;
	}

	// If path ends in slash (i.e. is a directory) then add "index.html".
	if (request_path[request_path.size() - 1] == '/')
	{
		request_path += "index.html";
	}

	// Determine the file extension.
	std::size_t last_slash_pos = request_path.find_last_of("/");
	std::size_t last_dot_pos = request_path.find_last_of(".");
	std::string extension;
	if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos)
	{
		extension = request_path.substr(last_dot_pos + 1);
	}

	// Open the file to send back.
	std::string full_path = docRoot + request_path;
	std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
	if (!is)
	{
		this->send(Response::not_found);
		return;
	}

	// Fill out the reply to be sent to the client.
	this->status = Response::ok;
	this->content.clear();
	char buf[512];
	while (is.read(buf, sizeof(buf)).gcount() > 0) {
		this->content.append(buf, (unsigned int)is.gcount());
	}
	headers["Content-Type"] = mime_types::extension_to_type(extension);
}

void Response::setHeader(const char* name, const char * value)
{
	headers[std::string(name)] = std::string(value);
}

void Response::setHeader(std::string &name, std::string &value)
{
	headers[name] = value;
}

void Response::setStatus(enum status_type status)
{
	this->status = status;
}

void Response::setCross(RequestPtr request)
{
	auto _iter = request->header_.find("Origin");
	if (_iter == request->header_.end())
	{
		this->setHeader(std::string("Access-Control-Allow-Origin"), std::string("*"));
	}
	else
	{
		this->setHeader("Access-Control-Allow-Origin", _iter->second.c_str());
		this->setHeader("Access-Control-Allow-Credentials", "true");

	}
}

void Response::end(Callback cb)
{
	if (cb == NULL) {
		cb = bind(&Response::defaultHandler, this, asio::placeholders::error);
	}
	if (!content.empty()) {
		if (headers.find("Content-Length") == headers.end()) {
			headers["Content-Length"] = boost::lexical_cast<std::string>(content.size());
		}
		if (headers.find("Content-Type") == headers.end()) {
			headers["Content-Type"] = "text/html";
		}
		asio::async_write(socket_, this->to_buffers(), cb);
	}
	else
	{
		cb(system::error_code(), 0);
	}
}

void Response::clear()
{
	headers.clear();
	content.clear();
}

void Response::defaultHandler(system::error_code)
{
}

