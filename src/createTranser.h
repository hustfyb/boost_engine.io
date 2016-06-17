#pragma once
#include "ObjectFactory.h"
class Shape
{
public:
	Shape();
	~Shape();

private:

};

template <class DerivedShape> class RegisterShapeClass
{
public:
	static Shape * Create()
	{
		return new DerivedShape;
	}
	RegisterShapeClass(const std::string& strShapeId)
	{
		ObjectFactory<Shape, std::string>::Instance()->Register(strShapeId, RegisterShapeClass::Create);
	}
};
#define ClassNameToString(x) #x

