#pragma once
#include "ObjectFactory.h"
#include "Request.hpp"
#include "Response.hpp"
#include "EngineIoParser.hpp"
class EngineSocket;
class TranserBase
{
public:
	TranserBase();
	virtual ~TranserBase();
	static TranserBase * CreateTranserByName(const std::string& className);
	static bool existTranser(const std::string& className);
	static std::vector<std::string> &getTranserNames();
	static std::vector<std::string> names;
	std::string name_;
	virtual void init(RequestPtr request, ResponsePtr response) = 0;
	virtual void onRequest(RequestPtr request, ResponsePtr response)=0;
	virtual void sendPacket(int type, std::string &data) = 0;


	virtual void sendPacket(EngineIoParser::Packet &pa) {
		sendPacket(pa.type, pa.data);
	};
	void setSocket(EngineSocket*engineSocket) {
		engineSocket_ = engineSocket;
	};
	EngineSocket *engineSocket_;
	std::string id_;
};
typedef TranserBase Transer;
template <class Transer> class RegisterTranserClass
{
public:
	static TranserBase * Create()
	{
		return new Transer;
	}
	RegisterTranserClass(const std::string& className)
	{
		TranserBase::names.push_back(className);

		ObjectFactory<TranserBase, std::string>::Instance()->Register(className, RegisterTranserClass::Create);
	}
};
