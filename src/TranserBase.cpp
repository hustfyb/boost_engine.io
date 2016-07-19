#include "header.hpp"
#include "TranserBase.hpp"

TranserBase::TranserBase()
{
}


TranserBase::~TranserBase()
{
}

TranserBase * TranserBase::CreateTranserByName(const std::string& className)
{
	TranserBase *obj = ObjectFactory<TranserBase, std::string>::Instance()->CreateObject(className);
	if (obj) obj->name_ = className;
	return obj;
}

bool TranserBase::existTranser(const std::string& className)
{
	auto _iter = find(names.begin(), names.end(), className);
	return (_iter != names.end());
}

std::vector<std::string> & TranserBase::getTranserNames()
{
	return names;
}

