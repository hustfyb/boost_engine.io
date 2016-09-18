#include "header.hpp"
#include "WebsocketTranser.hpp"
#include "EngineIoParser.hpp"
RegisterTranserClass<WebsocketTranser> RegisterWebsocket("websocket");
WebsocketTranser::WebsocketTranser()
{
}


WebsocketTranser::~WebsocketTranser()
{
	ws_->sigMessage.disconnect_all_slots();
	ws_->sigClose.disconnect_all_slots();
}

void WebsocketTranser::sendPacket(int type, std::string &data)
{
	std::string payload = EngineIoParser::encodePacket(type, data);
	ws_->sendData(payload);
}

void WebsocketTranser::setHandler(WebSocketPtr ws)
{
	ws_ = ws;
	ws->sigMessage.connect(bind(&WebsocketTranser::onMessage, this, _1));
}

void WebsocketTranser::onMessage(WebSocketPtr ws) 
{
	LOG(debug) << "recv data";
	EngineIoParser::PacketPtr  paPtr= EngineIoParser::decodePacket(ws->wParser_.data_,false);
	engineSocket_->onPacket(paPtr);
}
