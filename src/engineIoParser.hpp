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

	int encodePacket(engineIoState type, std::string &data);
};

