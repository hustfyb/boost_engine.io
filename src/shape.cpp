#include "createTranser.h"
Shape::Shape()
{
}

Shape::~Shape()
{
}

Shape * CreateShapeById(const std::string& strShapeId)
{
	return Factory<Shape, std::string>::Instance()->CreateObject(strShapeId);
}