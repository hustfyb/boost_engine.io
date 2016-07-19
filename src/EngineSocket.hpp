#pragma once
#include "Request.hpp"
#include "Response.hpp"
#include "TranserBase.hpp"
class EngineSocket
{
	typedef enum 
	{
		opening=1,
		open
	}ReadyState;
public:
	EngineSocket(std::string &, shared_ptr<TranserBase> , RequestPtr, ResponsePtr);
	~EngineSocket();
	RequestPtr request_;
	ResponsePtr response_;
	shared_ptr<TranserBase> transport_;
	std::string id_;
	bool upgrading_;
	bool upgraded_;
	ReadState readyState_;
private:
	void onOpen();
};

