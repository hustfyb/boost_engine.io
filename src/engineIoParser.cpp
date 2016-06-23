#include "header.hpp"
#include "engineIoParser.hpp"

namespace engineIoParser {
	int encodePacket(engineIoState type, std::string &data)
	{
		data.insert(0, lexical_cast<std::string>(type));
		return 0;
	}

	int encodePayloadAsBinary(std::string data){
		std::string head;
		int length = data.length();
		while (length>0){
			head = head + lexical_cast<std::string>(length % 10);
			length = length / 10;
		}
		head.insert(head.begin(), (char)0);
		head.insert(head.end(), (char)255);
		data.insert(0,data);
		return 0;
	}
}

