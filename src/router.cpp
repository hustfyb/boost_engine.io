//
// file_handler.cpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "router.hpp"
#include <string>
#include <boost/lexical_cast.hpp>
#include "Response.hpp"
#include "request.hpp"

namespace httpServer {

	router::router()
	{
	}

	bool router::operator()(boost::shared_ptr<Request> req, boost::shared_ptr<Response> res)
	{
		// Decode url to path.
		if (!url_decode(req->uri, req->path))
		{
			res->send(Response::bad_request);
			return true;
		}

		// Request path must be absolute and not contain "..".
		if (req->path.empty() || req->path[0] != '/'
			|| req->path.find("..") != std::string::npos)
		{
			res->send(Response::bad_request);
			return true;
		}

		//// If path ends in slash (i.e. is a directory) then add "index.html".
		//if (request_path[request_path.size() - 1] == '/')
		//{
		//  request_path += "index.html";
		//}

		if (httpHandlerContainer.find(req->path)==httpHandlerContainer.end()){
			return false;
		}

		httpHandlerContainer[req->path]()->handleRequest(req,res);
		return true;

		//req.path = request_path.c_str();
		//// Determine the file extension.
		//std::size_t last_slash_pos = request_path.find_last_of("/");
		//std::size_t last_dot_pos = request_path.find_last_of(".");
		//std::string extension;
		//if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos)
		//{
		//  extension = request_path.substr(last_dot_pos + 1);
		//}

		//// Open the file to send back.
		//std::string full_path = doc_root_ + request_path;
		//std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
		//if (!is)
		//{
		//  rep = reply::stock_reply(reply::not_found);
		//  return;
		//}

		//// Fill out the reply to be sent to the client.
		//rep.status = reply::ok;
		//char buf[512];
		//while (is.read(buf, sizeof(buf)).gcount() > 0)
		//  rep.content.append(buf, is.gcount());
		//rep.headers.resize(2);
		//rep.headers[0].name = "Content-Length";
		//rep.headers[0].value = boost::lexical_cast<std::string>(rep.content.size());
		//rep.headers[1].name = "Content-Type";
		//rep.headers[1].value = mime_types::extension_to_type(extension);
	}
	bool router::url_decode(const std::string& in, std::string& out)
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
			else
			{
				out += in[i];
			}
		}
		return true;
	}

	//void router::addHandler( std::string action,RequestHandler request_handler )



	void router::addTest( std::string action,boost::function<void()> )
	{
		LOGF;
	}

	void router::addHandler( std::string action,boost::function<boost::shared_ptr<RequestHandler> ()> creater )
	{
		httpHandlerContainer[action]=creater;		
	}
} // namespace httpServer
