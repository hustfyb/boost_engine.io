#pragma once
#include "header.hpp"
#include "DLog.h"



DLog::DLog()
{
}


DLog::~DLog()
{
}

#include <iostream>
#include <string>

#include <boost/filesystem.hpp>

#include <boost/log/support/date_time.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/detail/format.hpp>
#include <boost/log/detail/thread_id.hpp>
#include <boost/log/detail/light_rw_mutex.hpp>
namespace logging = boost::log;
namespace src = boost::log::sources;
namespace keywords = boost::log::keywords;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;

BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, src::logger_mt)
boost::log::sources::severity_logger<boost::log::trivial::severity_level > DLog::s_slg;

void DLog::init(const string & dir)
{
	if (boost::filesystem::exists(dir) == false)
	{
		boost::filesystem::create_directories(dir);
	}

	auto pSink = logging::add_file_log
	(
		keywords::open_mode = std::ios::app,
		keywords::file_name = dir + "/%Y%m%d.log",
		keywords::rotation_size = 10 * 1024 * 1024,
		keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
		//keywords::format = "[%TimeStamp% %ThreadID%]: %Message%"
		keywords::format =
		(
			expr::stream
			<< "[" << expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
			<< " " << expr::attr< boost::log::aux::thread::id >("ThreadID")
			<< " " << logging::trivial::severity
			<< "] " << expr::smessage
			)
	);
	pSink->locked_backend()->auto_flush(true);
	//pSink->imbue(std::locale("zh_CN.UTF-8")); // ±¾µØ»¯ 
	logging::add_common_attributes();
}


void DLog::log(const string & msg)
{
	src::logger lg;
	BOOST_LOG(lg) << msg;
}

#ifdef BOOST_ALL_NO_LIB
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
#include <libs/log/src/text_ostream_backend.cpp>
#include <libs/log/src/text_file_backend.cpp>
#include <libs/log/src/text_multifile_backend.cpp>
#include <libs/log/src/syslog_backend.cpp>
#include <libs/log/src/thread_specific.cpp>
#include <libs/log/src/once_block.cpp>
#include <libs/log/src/timestamp.cpp>
#include <libs/log/src/threadsafe_queue.cpp>
#include <libs/log/src/event.cpp>
#include <libs/log/src/trivial.cpp>
#include <libs/log/src/spirit_encoding.cpp>
#include <libs/log/src/format_parser.cpp>
#include <libs/log/src/date_time_format_parser.cpp>
#include <libs/log/src/named_scope_format_parser.cpp>
#include <libs/log/src/unhandled_exception_count.cpp>
#include <libs/log/src/dump.cpp>
#include <libs/log/src/light_rw_mutex.cpp>
//#include <libs/log/src/light_rw_mutex.cpp>

//////////////////////////////////////////////////////////////////////////
//filesystem
//////////////////////////////////////////////////////////////////////////
#include <libs/filesystem/src/codecvt_error_category.cpp>
#include <libs/filesystem/src/path.cpp>
#include <libs/filesystem/src/operations.cpp>
#include <libs/filesystem/src/path_traits.cpp>
#include <libs/filesystem/src/portability.cpp>
#include <libs/filesystem/src/unique_path.cpp>
#include <libs/filesystem/src/utf8_codecvt_facet.cpp>
#include <libs/filesystem/src/windows_file_codecvt.hpp>
#include <libs/filesystem/src/windows_file_codecvt.cpp>
#endif 
