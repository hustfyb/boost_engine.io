// SocketIOServer.cpp : 定义控制台应用程序的入口点。
//

#include "header.hpp"
// #include "Server.hpp"
// #include "Setting.hpp"
// #include "EngineIo.hpp"
// int main()
// {
// 	g_setting.setConfig(std::string("config.json"));
//  	asio::io_service io_service;
//  	shared_ptr<Server> httpServer=make_shared<Server>(io_service); 
// 
// 	EngineIo engineIo;
// 	httpServer->addFilter("/engine.io/.*", engineIo);
//  	httpServer->startListen(system::error_code());
// 	io_service.run();
//     return 0;
// }


////////////////////////File System///////////////////////////////////////
#include <libs/filesystem/src/codecvt_error_category.cpp>
#include <libs/filesystem/src/operations.cpp>
//#include <libs/filesystem/src/path.cpp>
#include <libs/filesystem/src/path_traits.cpp>
#include <libs/filesystem/src/portability.cpp>
#include <libs/filesystem/src/unique_path.cpp>
#include <libs/filesystem/src/utf8_codecvt_facet.cpp>
#include <libs/filesystem/src/windows_file_codecvt.cpp>

////////////////////////LOG Part//////////////////////////////////////////
#include <libs/log/src/attribute_name.cpp>
#include <libs/log/src/attribute_set.cpp>
#include <libs/log/src/attribute_value_set.cpp>
#include <libs/log/src/code_conversion.cpp>
#include <libs/log/src/core.cpp>
#include <libs/log/src/record_ostream.cpp>
#include <libs/log/src/severity_level.cpp>
#include <libs/log/src/global_logger_storage.cpp>
#include <libs/log/src/named_scope.cpp>
#include <libs/log/src/process_name.cpp>
#include <libs/log/src/process_id.cpp>
#include <libs/log/src/thread_id.cpp>
#include <libs/log/src/timer.cpp>
#include <libs/log/src/exceptions.cpp>
#include <libs/log/src/default_attribute_names.cpp>
#include <libs/log/src/default_sink.cpp>

#include <libs/log/src/unhandled_exception_count.cpp>
#include <libs/log/src/thread_specific.cpp>

#include <libs/log/src/light_rw_mutex.cpp>
#include <libs/log/src/once_block.cpp>

#include <boost/log/trivial.hpp>

int main(int, char*[])
{
	BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
	BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
	BOOST_LOG_TRIVIAL(info) << "An informational severity message";
	BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
	BOOST_LOG_TRIVIAL(error) << "An error severity message";
	BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

	return 0;
}