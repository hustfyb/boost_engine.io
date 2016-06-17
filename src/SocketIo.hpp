#pragma once
#include "Request.hpp"
#include "Response.hpp"
#include <boost/unordered_map.hpp>
#include "uuid_t.hpp"
namespace SocketIo {

	typedef struct {
		std::string transport;
		std::string sessionid;
		std::string i;
		std::string oriurl;
	} transport_info;

	bool match(Request &request, Response &response, function<void(system::error_code, std::size_t)> cb);
//	void handle_handshake(Request &request, Response &response, function<void(system::error_code, std::size_t)> cb);
}