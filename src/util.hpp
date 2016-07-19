

#pragma once
namespace util {
	std::string UrlEncode(const std::string& str);
	std::string UrlDecode(const std::string& str);
	int parseQueryString(std::string &url, std::map<std::string, std::string> &query);
	std::string ptToJsonStr(property_tree::ptree pt);
}

