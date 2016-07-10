#include "header.hpp"
#include "SocketIo.hpp"
#include <boost/xpressive/xpressive.hpp>
#include <boost/format.hpp>
#include "Setting.hpp"
#include "TranserBase.h"
using namespace xpressive;
namespace SocketIo {
	unordered_map<std::string, shared_ptr<session_t> > session_map;

	static char *transport_url_reg = "^/[^/]*/\\d{1}/([^/]*)/([^?|#]*).*?(i=(\\d+))?$";
	static char *transport_message_reg = "(\\d):(\\d+\\+?)?:(/[^:]*)?:?(.*)?";
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
		uuid_t uuid;
		shared_ptr<session_t> session =make_shared<session_t>();
		session->sid = uuid.toString();
// 		session->queue = NULL;
// 		session->client = NULL;
// 		session->endpoint = NULL;
		session->state = CONNECTING_STATE;

//		ev_timer *timeout = &session->close_timeout;
//		timeout->data = g_strdup(uuidBuff);
//		ev_timer_init(timeout, clear_handshake_cb, global_config->server_close_timeout, 0);
//		ev_timer_start(ev_default_loop(0), timeout);
		session_map[session->sid]= session;

		format fmt("%s:%d:%d:%s");
		fmt % session->sid % g_setting.getHeartbeat_timeout()
			% g_setting.getClose_timeout() % g_setting.getTransports();
		response.sendData(fmt.str(), cb);
	}

 	bool url_2_struct(Request &request) {
		cregex reg = cregex::compile(transport_url_reg,icase);
		cmatch what;
 		if (regex_match(request.url.c_str(), what, reg)) {
			std::string sessionid= what[2];
			if (session_map.find(sessionid) != session_map.end()) {
				request.sessionid = what[2];
				request.session = session_map[sessionid];
				request.transport = what[1];
			}
 			//trans_info.oriurl = input_string;
 			
 			//trans_info.i = what[3];
			//erase_first(trans_info.i, "i=");
 		}
 		else {
 			return false;
 		}
 		return true;
 	}

	int handle_transport(Request &request, Response &response, function<void(system::error_code, std::size_t)> cb) {
		std::vector<std::string> tt = TranserBase::getTransersName();
		Transer *transer = TranserBase::CreateTranserByName(request.transport);
		//if session no data
		//transer->output
		return 0;
	}
	void handleContinue(Request &request, Response &response, function<void(system::error_code, std::size_t)> cb) {
		url_2_struct(request);
		if (request.sessionid.empty()){
			response.send(Response::bad_request,cb);
		}
		else {
			handle_transport(request, response, cb);
		}
	}

	bool matchContinue(std::string &url)
	{
		using namespace xpressive;
		cregex reg = cregex::compile("^/[^/]*/\\d{1}/[^/]*/([^/]*)");
		cmatch what;
 		bool matchResult = regex_match(url.c_str(),reg);
		return matchResult;
	}

	bool match(Request &request, Response &response, function<void(system::error_code, std::size_t)> cb) {
		if (matchHandShake(request.url)) {
			handle_handshake(request, response, cb);
			return true;
		}
		else if (matchContinue(request.url)) {
			handleContinue(request, response, cb);
			return true;
		}
		return false;
	}

}