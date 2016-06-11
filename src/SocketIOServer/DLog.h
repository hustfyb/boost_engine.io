#pragma once
#include <string>
#include <boost/log/trivial.hpp>


using std::string;



class DLog
{
public:
	DLog();
	~DLog();
	static void init(const string & dir);
	static void log(const string & msg);
	
	static boost::log::sources::severity_logger<boost::log::trivial::severity_level > s_slg;
};



#define LOG_DEBUG\
    BOOST_LOG_SEV((DLog::s_slg),(boost::log::trivial::debug))
#define LOG_INFO\
    BOOST_LOG_SEV((DLog::s_slg),(boost::log::trivial::info))
#define LOG_ERROR\
    BOOST_LOG_SEV((DLog::s_slg),(boost::log::trivial::error))
#define LOG_WARNING\
    BOOST_LOG_SEV((DLog::s_slg),(boost::log::trivial::warning))
