#pragma once

class FilterBase
{
public:
	virtual void process(shared_ptr<Request>, shared_ptr<Response>) = 0;

private:

};

