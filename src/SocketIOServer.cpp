// SocketIOServer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "header.hpp"
#include "Server.hpp"
#include "Setting.hpp"
int main()
{
	g_setting.setConfig(std::string("config.json"));
 	asio::io_service io_service;
 	shared_ptr<Server> httpServer=make_shared<Server>(io_service); 
 	httpServer->startListen(system::error_code());
	io_service.run();
    return 0;
}

