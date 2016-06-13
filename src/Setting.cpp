#include "header.hpp"
#include "Setting.hpp"
using namespace std;

Setting::Setting()
{
}


Setting::~Setting()
{
}

void Setting::setConfig(std::string &fileName)
{
	try
	{
		read_json(fileName, m_config);
	}
	catch (...)
	{
		logf << "config file error\r\n";
	}

}

std::string Setting::getAddress()
{
	return m_config.get("address", "0.0.0.0");
}

std::string Setting::getPort()
{
	return m_config.get("port", "80");
}

std::string Setting::getRoot()
{
	return m_config.get("root", "web");
}

Setting g_setting;