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
		, error
	}EngineIoType;

	typedef struct 
	{
		int type;
		std::string  data;
	}Packet;
	typedef shared_ptr<Packet> PacketPtr;
	typedef std::vector<PacketPtr> PacketVector;
	std::string encodePacket(Packet &pa);
	std::string encodePacket(int type, std::string &data);
	std::string encodePayloadAsBinary(std::string &data);
	PacketPtr decodePacket(std::string &msg, bool binaryType);
	shared_ptr<PacketVector> decodePayload(std::string &data, bool binary=false);
};

