#pragma once
#include "header.hpp"
#include "../submodules/http-parser/http_parser.h"
class Request
{
public:
	Request();
	~Request();
	tribool parse(char *,std::size_t);
	std::string url;
	std::map<std::string, std::string> header;
private:
	http_parser m_parse;
	http_parser_settings m_httpSetting;

	std::string m_head;
public:
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
};

