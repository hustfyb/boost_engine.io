#pragma once

class FilterBase
{
public:
	virtual void process(Request&, Response&, Callback) = 0;

private:

};

