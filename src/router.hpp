//
// file_handler.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef router_h__
#define router_h__

#include <string>
#include <utility>
#include <map>
#include <boost/function.hpp>
#include "RequestHandler.h"
#include "ScreenHandler.h"
using namespace std;
using namespace boost;
namespace httpServer {

class Response;
struct Request;


typedef boost::function<boost::shared_ptr<RequestHandler> ()> RequestHandlerCreater;
typedef std::map<string,RequestHandlerCreater> HttpHandlerContainer;
/// The common handler for all incoming requests.
class router
{
public:
	/// Construct with a directory containing files to be served.
	explicit router();

	/// Handle a request and produce a reply.
	bool operator()(boost::shared_ptr<Request> req, boost::shared_ptr<Response> rep);

	/// Perform URL-decoding on a string. Returns false if the encoding was
	/// invalid.
	static bool url_decode(const std::string& in, std::string& out);

	//void addHandler( std::string action,RequestHandler request_handler );
	//void addHandler( std::string action,boost::function<boost::shared_ptr<RequestHandler>()>);
	void addHandler( std::string action,RequestHandlerCreater creater);
	void addTest( std::string action,boost::function<void()>);
	
private:
	HttpHandlerContainer httpHandlerContainer;
};

} // namespace httpServer

#endif // router_h__
