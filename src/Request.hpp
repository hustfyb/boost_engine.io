#pragma once
#include "header.hpp"
#include "../submodules/http-parser/http_parser.h"
#include "uuid_t.hpp"
enum SESSION_STATE {
	DISCONNECTED_STATE = -2,
	DISCONNECTING_STATE = -1,
	CONNECTING_STATE = 0,
	CONNECTED_STATE = 1
};


class Request
{
public:
	typedef enum {
		http_begin,
		http_done
	}State;
	Request();
	~Request();
	tribool parse(char *,std::size_t);
	std::string url;
	std::map<std::string, std::string> header_;
	std::map<std::string, std::string> query_;
	std::string body_;
	std::string data_;
	unsigned int method_;
private:
	http_parser_settings m_httpSetting;
	http_parser m_parse;

public:
	bool upgrade();
	static int on_message_begin(http_parser*);
	static int on_url(http_parser*, const char *at, size_t length);
	static int on_status(http_parser*, const char *at, size_t length);
	static int on_header_field(http_parser*, const char *at, size_t length);
	static int on_header_value(http_parser*, const char *at, size_t length);
	static int on_headers_complete(http_parser*);
	static int on_body(http_parser*, const char *at, size_t length);
	static int on_message_complete(http_parser*);
// 	static int on_chunk_header(http_parser*);
// 	static int on_chunk_complete(http_parser*);

	State m_state;
	std::string m_head;
	void clear();
};

typedef shared_ptr<Request> RequestPtr;