//
// header.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once
#define BOOST_ALL_NO_LIB
#ifdef WIN32
#define _WIN32_WINNT 0x0501
#define _SCL_SECURE_NO_WARNINGS
#endif

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/signals2.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio.hpp>
#include <boost/assign.hpp>
#include <boost/foreach.hpp> 
#include <boost/io/ios_state.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/system/system_error.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

////////////////////LOG //////////////////////////////////////////////////
#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>

#define foreach BOOST_FOREACH
///////////////////Thread  ////////////////////////////////////////////
//#include <boost/thread.hpp>

///////////////////////STL STD ////////////////////////////////////////////
#include <string>
#include <iostream>
#include <map>
#include <vector>


#define logf std::cout<<__FUNCTION__<<":"
using namespace boost;

typedef boost::asio::ip::tcp tcp;
 
typedef function<void(system::error_code ec, std::size_t length)> Callback;

#define LOG(x) BOOST_LOG_TRIVIAL(x)<<"["<<__FUNCTION__<<":"<<__LINE__<<"]"<<" "


