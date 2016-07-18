#pragma once
#include "header.hpp"
namespace engineIoParser
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
	}EngineIoState;

	typedef shared_ptr<property_tree::ptree> PackagePtr;
	typedef std::vector<PackagePtr> PackageVector;
	std::string encodePacket(EngineIoState type, std::string &data);
	std::string encodePayloadAsBinary(std::string data);
	shared_ptr<PackageVector> decodePayload(std::string &data, bool binary=false);
};

