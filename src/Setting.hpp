#pragma once
#include "header.hpp"
class Setting
{
public:
	Setting();
	~Setting();
	void setConfig(std::string &fileName);
	
	std::string getAddress();
	std::string getPort();
	std::string getRoot();
	int getHeartbeat_timeout();
	int getClose_timeout();
	std::string getTransports();
private:
	property_tree::ptree m_config;
};

extern Setting g_setting;

