#include "header.hpp"
#include "engineIoParser.hpp"

namespace engineIoParser {
	std::string encodePacket(engineIoState type, std::string &data)
	{
		std::string result=lexical_cast<std::string>(type)+data;
		return result;
	}

	std::string encodePayloadAsBinary(std::string data){
		std::string result;
		int length = data.length();
		result.insert(result.end(), (char)0);
		while (length>0){
			result.insert(result.end(), (char)(length % 10));
			length = length / 10;
		}
		result.insert(result.end(), (char)255);
		result.append(data);
		return result;
	}
}

