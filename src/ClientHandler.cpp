#include "header.hpp"
#include "ClientHandler.h"

namespace httpServer {

	ClientHandler::ClientHandler(asio::io_service& io_service)
		:ios(io_service),m_socket(io_service)
	{
	}


	ClientHandler::~ClientHandler()
	{
		logf << "\r\n";
	}

#include <boost/asio/yield.hpp>
	void ClientHandler::run(system::error_code ec, std::size_t length)
	{
//		request_.reset(new Request);
		if (ec) {
			do
			{
				buffer_.reset(new ArrayBuffer);
				yield m_socket->async_read_some(boost::asio::buffer(*buffer_), bind(&ClientHandler::run,);

				// Parse the data we just received.
				boost::tie(valid_request_, boost::tuples::ignore)
					= request_parser_.parse(*request_,
						buffer_->data(), buffer_->data() + length);

				// An indeterminate result means we need more data, so keep looping.
			} while (boost::indeterminate(valid_request_));

			// Create the reply object that will be sent back to the client.
			reply_.reset(new Response(socket_));

			if (valid_request_)
			{
				// A valid request was received. Call the user-supplied function object
				// to process the request and compose a reply.
				if (!request_handler_(request_, reply_)) {
					file_handler_(*request_, *reply_);
					yield boost::asio::async_write(*socket_, reply_->to_buffers(), *this);

					// Initiate graceful connection closure.
					socket_->shutdown(tcp::socket::shutdown_both, ec);
				};
			}
			else {
				reply_->send(Response::bad_request);
			}

		}

	}
#include <boost/asio/unyield.hpp>

}