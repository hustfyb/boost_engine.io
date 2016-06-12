// SocketIOServer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "header.hpp"
#include "Server.hpp"

int main()
{
 	asio::io_service io_service;
 	shared_ptr<Server> httpServer=make_shared<Server>(io_service,"config.json"); 
 	httpServer->startListen(system::error_code());
	io_service.run();
    return 0;
}

