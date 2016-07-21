// SocketIOServer.cpp : 定义控制台应用程序的入口点。
//

#include "header.hpp"
#include "Server.hpp"
#include "Setting.hpp"
#include "EngineIo.hpp"
#include "EngineIoHandler.h"
void logInit()
{
	log::core::get()->set_filter
	(
		log::trivial::severity >= log::trivial::trace
	);
}

template <typename Handler>
shared_ptr<Handler> *createHandler()
{
	return make_shared<Handler>();
}

int main()
{
	g_setting.setConfig(std::string("config.json"));
 	asio::io_service io_service;
 	shared_ptr<Server> httpServer=make_shared<Server>(io_service); 
	EngineIo engineIo(io_service);
	engineIo.bindHandler(createHandler<EngineIoHandler>);
	httpServer->addFilter(".*/engine.io/.*", engineIo);
 	httpServer->startListen(system::error_code());
	io_service.run();
    return 0;
}

