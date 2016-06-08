// SocketIOServer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "header.hpp"
#include "Server.hpp"

using namespace httpServer;
int main()
{
 	asio::io_service io_service;
 	shared_ptr<Server> httpServer=make_shared<Server>(io_service,"0.0.0.0", "8888","./web"); 
 	httpServer->startListen(system::error_code());
	io_service.run();
    return 0;
}

