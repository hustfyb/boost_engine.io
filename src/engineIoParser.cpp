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
		std::string temp;
		while (length>0){
			temp.insert(temp.end(), (char)(length % 10));
			length = length / 10;
		}
		for (std::string::reverse_iterator _iter=temp.rbegin();_iter!=temp.rend();_iter++)
		{
			result.insert(result.end(), *_iter);
		}
		result.insert(result.end(), (char)255);
		result.append(data);
		return result;
	}
}

