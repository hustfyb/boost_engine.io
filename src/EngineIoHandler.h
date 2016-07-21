#pragma once
class EngineSocket;
class EngineIoHandler
{
public:
	virtual void onConnect(EngineSocket*)=0;
	virtual void onMessage(EngineSocket*,std::string &data) = 0;
	virtual void onClose(EngineSocket*) = 0;
};

