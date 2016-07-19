#pragma once
#include "header.hpp"
namespace EngineIoParser
{
	typedef enum
	{
		open = 0
		, close    // non-ws
		, ping
		, pong
		, message
		, upgrade
		, noop
	}EngineIoType;

	typedef struct 
	{
		int type;
		std::string  data;
	}Package;
	typedef shared_ptr<Package> PackagePtr;
	typedef std::vector<PackagePtr> PackageVector;
	std::string encodePacket(EngineIoType type, std::string &data);
	std::string encodePayloadAsBinary(std::string &data);
	PackagePtr decodePacket(std::string &msg, bool binaryType);
	shared_ptr<PackageVector> decodePayload(std::string &data, bool binary=false);
};

