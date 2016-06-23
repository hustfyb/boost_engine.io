#pragma once
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
	}engineIoState;

	std::string encodePacket(engineIoState type, std::string &data);
	std::string encodePayloadAsBinary(std::string data);
};

