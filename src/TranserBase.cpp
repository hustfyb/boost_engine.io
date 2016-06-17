#include "header.hpp"
#include "TranserBase.h"

std::vector<std::string> TranserBase::names;
TranserBase::TranserBase()
{
}


TranserBase::~TranserBase()
{
}

TranserBase * TranserBase::CreateTranserByName(const std::string& className)
{
	return ObjectFactory<TranserBase, std::string>::Instance()->CreateObject(className);
}

std::vector<std::string> & TranserBase::getTransersName()
{
	return names;
}
