#pragma once
#include "header.hpp"
#include "Server.hpp"
class engineIo
{
public:
	void operator()(Request&, Response&, Callback);

};

