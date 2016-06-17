#pragma once
#include "ObjectFactory.h"
class TranserBase
{
public:
	TranserBase();
	virtual ~TranserBase();
	static TranserBase * CreateTranserByName(const std::string& className);
	static  std::vector<std::string> &getTransersName();
	static std::vector<std::string> names;
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