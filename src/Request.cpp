#include "header.hpp"
#include "Request.hpp"
#include "util.hpp"
using namespace std;


Request::Request()
{
	m_state = http_begin;
	http_parser_init(&m_parse,HTTP_REQUEST);
	m_parse.data = this;

	m_httpSetting.on_message_begin = Request::on_message_begin;
	m_httpSetting.on_url = Request::on_url;
	m_httpSetting.on_status =Request::on_status ;
	m_httpSetting.on_header_field = Request::on_header_field;
	m_httpSetting.on_header_value = Request::on_header_value;
	m_httpSetting.on_headers_complete = Request::on_headers_complete;
	m_httpSetting.on_body = Request::on_body;
	m_httpSetting.on_message_complete = Request::on_message_complete;
}


Request::~Request()
{
}

tribool Request::parse(char *data,std::size_t dSize)
{
	size_t rt=http_parser_execute(&m_parse, &m_httpSetting, data, dSize);
	logf << rt << "\r\n";
	if (rt == 0) {
		return false;
	};
	if (m_state == http_done) {
		return true;
	}	
	return indeterminate;
}

int Request::on_url(http_parser* parse, const char *at, size_t length)
{
	Request *request = (Request*)parse->data;
	request->url.assign(at, length);
	util::parseQueryString(request->url,request->query);
	return 0;
}

int Request::on_status(http_parser*, const char *at, size_t length)
{
	logf << "\r\n";
	return 0;

}

int Request::on_header_field(http_parser* parse, const char *at, size_t length)
{
	Request *request = (Request*)parse->data;
	request->m_head.assign(at, length);
	return 0;
}

int Request::on_header_value(http_parser* parse, const char *at, size_t length)
{
	Request *request = (Request*)parse->data;
	string value(at, length);
	request->header.insert(pair<string, string>(request->m_head, value));
	return 0;
}

int Request::on_headers_complete(http_parser*)
{
	logf << "\r\n";
	return 0;

}

int Request::on_body(http_parser*, const char *at, size_t length)
{
	logf << "\r\n";
	return 0;

}

int Request::on_message_complete(http_parser*)
{
	logf << "\r\n";
	return 0;
}

bool Request::upgrade()
{
	return m_parse.upgrade;
}

int Request::on_message_begin(http_parser*parse)
{
	Request *request = (Request*)parse->data;
	request->m_state = http_done;
	return 0;
}

