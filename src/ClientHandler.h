#pragma once
#include "header.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "../submodules/http-parser/http_parser.h"

namespace httpServer {
	class ClientHandler:asio::coroutine,
		public enable_shared_from_this<ClientHandler>
	{
	public:
		explicit ClientHandler(asio::io_service& io_service);
		~ClientHandler();
		void run(system::error_code ec, std::size_t length);
		tcp::socket m_socket;
	private:
		asio::io_service &ios;
		typedef array<char, 8192> ArrayBuffer;
		shared_ptr<ArrayBuffer> buffer_;
		shared_ptr<http_parser> parser;
		Request			request;
		Response		response;

		function<void(const Request&, Response &)>  file_handler_;

	};
}

