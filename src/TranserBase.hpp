#pragma once
#include "ObjectFactory.h"
class Request;
class Response;
class TranserBase
{
public:
	TranserBase();
	virtual ~TranserBase();
	static TranserBase * CreateTranserByName(const std::string& className);
	static bool existTranser(const std::string& className);
	static std::vector<std::string> &getTranserNames();
	static std::vector<std::string> names;
	virtual void onRequest(Request& request, Response& response, Callback cb)=0;
};
typedef TranserBase Transer;
template <class Transer> class RegisterTranserClass
{
public:
	static TranserBase * Create()
	{
		return new Transer;
	}
	RegisterTranserClass(const std::string& className)
	{
		TranserBase::names.push_back(className);

		ObjectFactory<TranserBase, std::string>::Instance()->Register(className, RegisterTranserClass::Create);
	}
};
