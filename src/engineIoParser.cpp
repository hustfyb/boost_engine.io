#include "header.hpp"
#include "EngineIoParser.hpp"

namespace EngineIoParser {
	std::string encodePacket(int type, std::string &data)
	{
		std::string result = lexical_cast<std::string>(type) + data;
		return result;
	}
	std::string encodePacket(Packet &data)
	{
		std::string result = lexical_cast<std::string>(data.type) + data.data;
		return result;
	}

	std::string encodePayloadAsBinary(std::string &data) {
		std::string result;
		int length = data.length();
		result.insert(result.end(), (char)0);
		std::string temp;
		while (length > 0) {
			temp.insert(temp.end(), (char)(length % 10));
			length = length / 10;
		}
		for (std::string::reverse_iterator _iter = temp.rbegin(); _iter != temp.rend(); _iter++)
		{
			result.insert(result.end(), *_iter);
		}
		result.insert(result.end(), (char)255);
		result.append(data);
		return result;
	}

	shared_ptr<PacketVector> decodePayload(std::string &data, bool binary/*=false*/)
	{
		Packet err = { EngineIoParser::error, "parser error" };
		shared_ptr<PacketVector> paVectorPtr = make_shared<PacketVector>();
		int pos = 0;
		int start = 0;
		pos = data.find_first_of(':', start + 1);
		while (pos >= 0)
		{

			int msgLength;
			try
			{
				msgLength = lexical_cast<int>(data.substr(start, pos - start));
				std::string msg = data.substr(pos + 1, msgLength);
				PacketPtr paPtr = decodePacket(msg, false);
				if (paPtr == NULL)
				{
					break;
				}
				else
				{
					paVectorPtr->push_back(paPtr);
				}
				start = pos + 1 + msgLength;
			}
			catch (const std::exception&)
			{
				LOG(error) << "payload length error";
				return NULL;
			}
			pos = data.find_first_of(':', start + 1);
		}
		return paVectorPtr;
	}

	PacketPtr decodePacket(std::string &msg, bool binaryType)
	{
		PacketPtr paPtr = make_shared<Packet>();
		if (!binaryType)
		{
			if (msg[0] == 'b')
			{
				throw std::exception("decodeBase64Packet is not implemented.");
			}
			paPtr->type = lexical_cast<int>(msg[0]);
			if (paPtr->type > noop || paPtr->type < open) {
				return NULL;
			}
			paPtr->data = msg.substr(1, msg.length() - 1);
			return paPtr;
		}
		else
		{
			throw std::exception("binaryType is not implemented.");
		}

	}
}

