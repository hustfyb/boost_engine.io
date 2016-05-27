#pragma once
#include "header.hpp"
namespace httpServer {

	class ClientHandler
	{
	public:
		explicit ClientHandler(asio::io_service& io_service);
		~ClientHandler();
		void run();
		tcp::socket m_socket;
	private:
		asio::io_service &ios;
	};
}

