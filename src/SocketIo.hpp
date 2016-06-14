#pragma once
#include "Request.hpp"
#include "Response.hpp"
#include "uuid_t.hpp"
namespace SocketIo {
	enum SESSION_STATE {
		DISCONNECTED_STATE = -2,
		DISCONNECTING_STATE = -1,
		CONNECTING_STATE = 0,
		CONNECTED_STATE = 1
	};
	
	typedef struct {
		shared_ptr<uuid_t> sessionid;
	//	client_t *client;
	//	GQueue *queue;
	//	char *endpoint;
		int state; /* -2:disconnected; -1:disconnecting; 0:connecting; 1:connected; */
	//	ev_timer close_timeout;
	} session_t;

	bool match(std::string &url);
	void handle_handshake(Request &request, Response &response, function<void(system::error_code, std::size_t)> cb);
}