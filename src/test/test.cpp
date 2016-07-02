// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../header.hpp"
// #define BOOST_TEST_MAIN
// #include <boost/test/included/unit_test.hpp>
// 
// #define BOSST_TEST_INCLUDED
// #include <boost/test/unit_test.hpp>
// 
// #include "../engineIoParser.hpp"
// using namespace boost;
// using namespace engineIoParser;
// BOOST_AUTO_TEST_SUITE(t_engineIo)
// 
// BOOST_AUTO_TEST_CASE(t_engineIo_parse)
// {
// 	std::string str("123");
// 	std::string packet=encodePacket(open, str);
// 	BOOST_CHECK_EQUAL(packet, "0123");
// 	std::string payload = encodePayloadAsBinary(packet);
// 	std::string data("___0123");
// 	data[0] = 0; data[1] = 4; data[2] = 0xff;
// 	BOOST_CHECK_EQUAL(data, payload);
// }
// 
// BOOST_AUTO_TEST_SUITE_END()

#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>

////////////////////////File System///////////////////////////////////////
#include <libs/filesystem/src/codecvt_error_category.cpp>
//#include <libs/filesystem/src/operations.cpp>
#include <libs/filesystem/src/path.cpp>
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
#include <libs/log/src/default_attribute_names.cpp>
#include <libs/log/src/default_sink.cpp>
//#include <libs/log/src/text_ostream_backend.cpp>
//#include <libs/log/src/text_file_backend.cpp>
//#include <libs/log/src/text_multifile_backend.cpp>
#include <libs/log/src/syslog_backend.cpp>
#include <libs/log/src/thread_specific.cpp>
#include <libs/log/src/once_block.cpp>
#include <libs/log/src/timestamp.cpp>
//#include <libs/log/src/threadsafe_queue.cpp>
#include <libs/log/src/trivial.cpp>



#include <libs/log/src/timer.cpp>
#include <libs/log/src/exceptions.cpp>

#include <libs/log/src/unhandled_exception_count.cpp>

#include <libs/log/src/light_rw_mutex.cpp>
#include <libs/log/src/dump.cpp>





int main(int, char*[])
{
	BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
	BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
	BOOST_LOG_TRIVIAL(info) << "An informational severity message";
	BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
	BOOST_LOG_TRIVIAL(error) << "An error severity message";
	BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

// 	// Filtering can also be applied
// 	using namespace boost::log;
// 
// 	core::get()->set_filter
// 	(
// 		trivial::severity >= trivial::info
// 	);
// 
// 	// Now the first two lines will not pass the filter
// 	BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
// 	BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
// 	BOOST_LOG_TRIVIAL(info) << "An informational severity message";
// 	BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
// 	BOOST_LOG_TRIVIAL(error) << "An error severity message";
// 	BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";
	return 0;
}