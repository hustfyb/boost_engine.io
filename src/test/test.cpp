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

void logInit()
{
// 	log::core::get()->set_filter
// 	(
// 		log::trivial::severity >= log::trivial::info
// 	);
}

int main(int, char*[])
{
	logInit();
	BOOST_LOG_TRIVIAL(trace) <<__FUNCTION__<<"["<<__LINE__<<"] "<< "A trace severity message";
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