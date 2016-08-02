// test.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include "../header.hpp"

#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>

#define BOSST_TEST_INCLUDED
#include <boost/test/unit_test.hpp>

#include "../EngineIoParser.hpp"
using namespace boost;
using namespace EngineIoParser;
BOOST_AUTO_TEST_SUITE(t_engineIo)

BOOST_AUTO_TEST_CASE(t_engineIo_parse)
{
	Packet pa ={ open,"123" };
	std::string packet=encodePacket(pa);
	BOOST_CHECK_EQUAL(packet, "0123");
	std::string payload = encodePayloadAsBinary(packet);
	std::string data("___0123");
	data[0] = 0; data[1] = 4; data[2] = 0xff;
	BOOST_CHECK_EQUAL(data, payload);
}

BOOST_AUTO_TEST_SUITE_END()