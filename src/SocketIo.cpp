#include "header.hpp"
#include "SocketIo.hpp"
#include <boost/xpressive/xpressive.hpp>
#include <boost/format.hpp>
#include "Setting.hpp"
namespace SocketIo {
	bool match(Request &request, Response &response, function<void(system::error_code, std::size_t)> cb) {
		if (matchHandShake(request.url)) {
			handle_handshake(request, response, cb);
		}else if (matchContinue(request.url)) {
		
		}
	}
	bool matchHandShake(std::string &url)
	{
		using namespace xpressive;
		cregex reg = cregex::compile("^/([^/])*/\\d{1}/\\?t=\\d+.*?");
		bool matchResult = regex_match(url.c_str(), reg);
		return matchResult;
	}

	void handle_handshake(Request &request, Response &response, function<void(system::error_code, std::size_t)> cb)
	{
//		char uuidBuff[36];

		shared_ptr<session_t> session =make_shared<session_t>();
		session->sessionid = make_shared<uuid_t>();
// 		session->queue = NULL;
// 		session->client = NULL;
// 		session->endpoint = NULL;
		session->state = CONNECTING_STATE;

//		ev_timer *timeout = &session->close_timeout;
//		timeout->data = g_strdup(uuidBuff);
//		ev_timer_init(timeout, clear_handshake_cb, global_config->server_close_timeout, 0);
//		ev_timer_start(ev_default_loop(0), timeout);

//		store_add(session->sessionid, session);

//		char body_msg[120];
		
		format fmt("%s:%d:%d:%s");
		fmt % session->sessionid % g_setting.getHeartbeat_timeout()
			% g_setting.getClose_timeout() % g_setting.getTransports();
		response.sendData(fmt.str(), cb);
//		sprintf(body_msg, "%s:%d:%d:%s",
// 		char http_msg[strlen(body_msg) + 200];
// 		sprintf(http_msg, RESPONSE_PLAIN, (int)strlen(body_msg), body_msg);
// 
// 		client_t *client = parser->data;
// 		write_output(client, http_msg, on_close);
	}

	bool matchContinue(std::string &url)
	{
		using namespace xpressive;
		cregex reg = cregex::compile("^/([^/])*/\\d{1}/\\?t=\\d+.*?");
		bool matchResult = regex_match(url.c_str(), reg);
		return matchResult;
	}

}