#include "header.hpp"
#include "WebSocket.h"
#include "util.hpp"
#include <boost/uuid/sha1.hpp>

#define WEBSOCKET_MAGIC_STRING				"258EAFA5-E914-47DA-95CA-C5AB0DC85B11"
#define WEBSOCKET_KEY_HEADER				"Sec-WebSocket-Key"
#define WEBSOCKET_HANDSHAKE_RESPONSE		"HTTP/1.1 101 WebSocket Protocol Handshake\r\nUpgrade: websocket\r\n%s\r\nServer: engine.io\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: %s\r\n\r\n"

#include <boost/archive/iterators/base64_from_binary.hpp>  
#include <boost/archive/iterators/binary_from_base64.hpp>  
#include <boost/archive/iterators/transform_width.hpp>  

bool Base64Encode(const std::string& input, std::string &output) {
	typedef boost::archive::iterators::base64_from_binary<boost::archive::iterators::transform_width<std::string::const_iterator, 6, 8> > Base64EncodeIterator;
	std::stringstream result;
	copy(Base64EncodeIterator(input.begin()), Base64EncodeIterator(input.end()), std::ostream_iterator<char>(result));
	size_t equal_count = (3 - input.length() % 3) % 3;
	for (size_t i = 0; i < equal_count; i++) {
		result.put('=');
	}
	output = result.str();
	return output.empty() == false;
}

bool Base64Decode(const std::string& input, std::string &output) {
	typedef boost::archive::iterators::transform_width<boost::archive::iterators::binary_from_base64<std::string::const_iterator>, 8, 6> Base64DecodeIterator;
	std::stringstream result;
	try {
		copy(Base64DecodeIterator(input.begin()), Base64DecodeIterator(input.end()), std::ostream_iterator<char>(result));
	}
	catch (...) {
		return false;
	}
	output = result.str();
	return output.empty() == false;
}

#include <boost/asio/yield.hpp>
boost::tuple<boost::tribool, int> WebsocketDataParser::parse(unsigned char *data, int length)
{
	unsigned int consumeBytes = 0;
	unsigned int dataStart;
	int i,j;
	tribool result= indeterminate;
	reenter(this){
		//head 
		if ((length - consumeBytes) < sizeof(head)) {
			return make_tuple(tribool(indeterminate), 0);
		}
		head = *(Head*)data;
		consumeBytes += sizeof(head);
		parserStage_ = 1;
		if (head.rsv != 0) {
			yield return make_tuple(false, consumeBytes);
		}
		else {
			yield return make_tuple(tribool(indeterminate), consumeBytes);
		}
		//dataLen & mask 
		if (head.pLen < 126) {
			dataStart = 0;
		}
		else if (head.pLen == 126) {
			dataStart = 2;
		}
		else if (head.pLen == 127) {
			dataStart = 8;
		}
		if (head.mask == 1) {
			if ((length - consumeBytes) < dataStart + 4) {
				return make_tuple((tribool)indeterminate, 0);
			}
			mask_[0] = data[dataStart];
			mask_[1] = data[dataStart + 1];
			mask_[2] = data[dataStart + 2];
			mask_[3] = data[dataStart + 3];
			dataStart += 4;
		}
		else {
			//客户端必须掩码（mask）它发送到服务器的所有帧（更多详细信息请参见5.3节）
			return make_tuple(false, 0);

// 			if ((length - consumeBytes) < dataStart) {
// 				return make_tuple((tribool)indeterminate, 0);
// 			}
		}
		if (head.pLen < 126) {
			dataLen_ = head.pLen;
		}
		else if (head.pLen == 126) {
			dataLen_ = (data[0] << 8) + data[1];
		}
		else if (head.pLen == 127) {
			dataLen_ = ((long long)data[0] << 56) +
						((long long)data[1] << 48) +
						((long long)data[2] << 40) +
						((long long)data[3] << 32) +
						(data[4] << 24) +
						(data[5] << 16) +
						(data[6] << 8) +
						(data[7])-8;
		}
		consumeBytes += dataStart;
		parserStage_ = 2;
		yield return make_tuple((tribool)indeterminate, consumeBytes);
		while (dataLen_>0)
		{
			//data
			consumeBytes = (unsigned int)std::min((long long)length, dataLen_);
			consumeBytes = std::min(consumeBytes, sizeof(this->msg_));
			if (head.mask) {
				for (i = 0, j = 0; i < dataLen_; i++, j++) {
					this->msg_[j] = (unsigned char)data[i] ^ mask_[j % 4];
				}
			}
			else {
				memcpy(this->msg_, data, consumeBytes);
			}
			dataLen_ -= consumeBytes;
			data += consumeBytes;
			if (dataLen_ > 0) {
				yield return make_tuple((tribool)indeterminate, consumeBytes);
			}
		}
		if (dataLen_ < 0) {
			return make_tuple(false, consumeBytes);
		}else {
			return make_tuple(true, consumeBytes);
		}
	}
	return make_tuple(true,0);
}

void WebsocketDataParser::clear()
{
	parserStage_=0;
}

WebSocket::WebSocket()
{
}


WebSocket::~WebSocket()
{
}


void WebSocket::process(RequestPtr req, ResponsePtr res, Callback cb)
{
	req_ = req;
	res_ = res;
	cb_ = cb;
	socket_ = res->getSocket();
	doWebSocket(system::error_code(), 0);
}


int WebSocket::generateHandshake(RequestPtr req, std::string &reply)
{
	std::string origin = MapGet(req->header_, "Origin","null");
	std::string host = MapGet(req->header_, "Host", "null");
	std::string additional_headers;
	additional_headers = "Origin: "+origin+"\r\nHost: "+host;
	std::string sec_websocket_key=MapGet(req->header_, WEBSOCKET_KEY_HEADER, "null");
	if (sec_websocket_key == "") {
		reply = "";
		return -1; // no sec-websocket-key
	}
	sec_websocket_key= sec_websocket_key+WEBSOCKET_MAGIC_STRING;

	uuids::detail::sha1 sha;
	sha.process_bytes(sec_websocket_key.c_str(),sec_websocket_key.length());
	unsigned int digest[5];
	sha.get_digest(digest);
	
	for (int i = 0; i < 5; i++) {
		digest[i]=htonl(digest[i]);
	}
	std::string sec_websocket_accept;
	Base64Encode(std::string((char*)digest,5*4), sec_websocket_accept);
	format fmt(WEBSOCKET_HANDSHAKE_RESPONSE);
	fmt%additional_headers % sec_websocket_accept;
	reply = fmt.str();
	return 0;
}
#define CallFromThis(x) bind(&x, shared_from_this(), _1, _2) 

void WebSocket::doWebSocket(system::error_code ec, size_t length)
{
	tribool parseResult = false;
	if (!ec)
	{
		reenter(this)
		{
			//handshake
			buffer_.reset(new ArrayBuffer);
			if (generateHandshake(req_, reply_) != 0) {
				return;
			}
			yield res_->getSocket()->async_write_some(buffer(reply_), CallFromThis(WebSocket::doWebSocket));

			//open
			while (true)
			{
				wParser_.clear();
				do {
					yield socket_->async_read_some(buffer(*buffer_), CallFromThis(WebSocket::doWebSocket));
					parseResult = this->getData(buffer_->data(), length);
				} while (indeterminate(parseResult));
				//data
			}
//			return cb_(system::error_code(), 0);
		}
	}
	else
	{
		LOG(error) << ec;
	}

}

boost::tribool WebSocket::getData(unsigned char *data, size_t length)
{
	tribool result; int cBytes;
	do{
		tie(result, cBytes) = wParser_.parse(data, length);
		if(indeterminate(result))
		{
			length -= cBytes;
			data += cBytes;
// 			if (wParser_.dataParse_)
// 			{
// 
// 			}
		}
	} while (indeterminate(result) && length > 0);
	//if (re)
	return result;
}

#include <boost/asio/unyield.hpp>
