#pragma once
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
class Setting
{
public:
	Setting();
	~Setting();
	void setConfig(std::string &fileName);
	
	std::string getAddress();
	std::string getPort();
	std::string getRoot();
private:
	property_tree::ptree m_config;
};

extern Setting g_setting;

