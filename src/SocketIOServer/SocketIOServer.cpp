// SocketIOServer.cpp : 定义控制台应用程序的入口点。
//

#include "header.hpp"
#include "Server.hpp"
#include "DLog.h"
using namespace httpServer;
int main()
{
	asio::io_service io_service;
 	shared_ptr<Server> httpServer=make_shared<Server>(io_service,"0.0.0.0", "8888");
 	httpServer->startListen();

	io_service.run();
    return 0;
}

