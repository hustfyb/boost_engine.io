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

class base
{
public:
	base();
	~base();

private:

};

base::base()
{
}

base::~base()
{
	std::cout << __FUNCTION__ << std::endl;
}
class  test
{
public:
	 test();
	~ test();
	shared_ptr<base> base_;
private:

};

 test:: test()
{
	base_ = make_shared<base>();
}

 test::~ test()
{
	std::cout << __FUNCTION__ << std::endl;
}
BOOST_AUTO_TEST_CASE(t_engineIo_parse)
{
	shared_ptr<base> bb;
	{
		shared_ptr<test> t = make_shared<test>();
		bb = t->base_;
		std::cout << "test count " << t.use_count()<<std::endl;
		std::cout << "base count " << t->base_.use_count() << std::endl;
	}

	Packet pa ={ open,"123" };
	std::string packet=encodePacket(pa);
	BOOST_CHECK_EQUAL(packet, "0123");
	std::string payload = encodePayloadAsBinary(packet);
	std::string data("___0123");
	data[0] = 0; data[1] = 4; data[2] = 0xff;
	BOOST_CHECK_EQUAL(data, payload);
}

BOOST_AUTO_TEST_SUITE_END()