#pragma once
#include "header.hpp"
#include "EngineIo.hpp"
#include "EngineIoParser.hpp"
#include "TranserBase.hpp"
class EngineSocket:public enable_shared_from_this<EngineSocket>
{
	typedef enum 
	{
		opening=1,
		open,
		closeing,
		closed
	}ReadyState;
public:
	EngineSocket(std::string &, EngineIo*, shared_ptr<TranserBase>, RequestPtr, ResponsePtr, io_service &);
	~EngineSocket();
	std::string id_;
	ReadyState readyState_;
	void onRequest(RequestPtr request, ResponsePtr response) const;
	void onPacket(EngineIoParser::PacketPtr paPtr);
	void setPingTimeout();
	void onOpen();
	void onClose(char *);
private:
	deadline_timer timer_;
	bool upgrading_;
	bool upgraded_;
	RequestPtr request_;
	ResponsePtr response_;
	EngineIo* engineIo_;
	shared_ptr<TranserBase> transport_;
	void pingTimeout(const boost::system::error_code& error);
};

