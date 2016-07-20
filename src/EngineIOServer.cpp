// SocketIOServer.cpp : 定义控制台应用程序的入口点。
//

#include "header.hpp"
#include "Server.hpp"
#include "Setting.hpp"
#include "EngineIo.hpp"
void logInit()
{
	log::core::get()->set_filter
	(
		log::trivial::severity >= log::trivial::trace
	);
}
int main()
{
	g_setting.setConfig(std::string("config.json"));
 	asio::io_service io_service;
 	shared_ptr<Server> httpServer=make_shared<Server>(io_service); 
	EngineIo engineIo(io_service);
	httpServer->addFilter(".*/engine.io/.*", engineIo);
 	httpServer->startListen(system::error_code());
	io_service.run();
    return 0;
}

