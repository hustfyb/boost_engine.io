// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>

#define BOSST_TEST_INCLUDED
#include <boost/test/unit_test.hpp>

using namespace boost;

BOOST_AUTO_TEST_SUITE(s_smart_ptr)

BOOST_AUTO_TEST_CASE(t_scoped_ptr)
{
	scoped_ptr<int> p(new int(874));
	BOOST_CHECK(p);
	BOOST_CHECK_EQUAL(*p, 874);
	p.reset();
	BOOST_CHECK(p == 0);
}

BOOST_AUTO_TEST_SUITE_END()