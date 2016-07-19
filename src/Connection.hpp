#pragma once
#include "header.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "../submodules/http-parser/http_parser.h"
#include "Server.hpp"
#include "FilterBase.hpp"
typedef std::map<std::string, FilterBase *> FilterMap;
class Server;

class Connection :asio::coroutine,
	public enable_shared_from_this<Connection>
{
public:
	explicit Connection(Server &);
	~Connection();
	void run(system::error_code ec, std::size_t length);
	tcp::socket m_socket;
	//void recvData(system::error_code ec, std::size_t length);
private:
	asio::io_service &ios;
	typedef array<char, 8192> ArrayBuffer;
	shared_ptr<ArrayBuffer> buffer_;
	Server			&server;
	shared_ptr<Request>			request_;
	shared_ptr<Response>		response_;
};

