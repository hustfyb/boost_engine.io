#include "header.hpp"
#include "ClientHandler.h"

namespace httpServer {

	ClientHandler::ClientHandler(asio::io_service& io_service)
		:ios(io_service),m_socket(io_service)
	{
	}


	ClientHandler::~ClientHandler()
	{
		logf << "\r\n";
	}


	void ClientHandler::run()
	{
		logf << m_socket.remote_endpoint() << "\r\n";
	}

}