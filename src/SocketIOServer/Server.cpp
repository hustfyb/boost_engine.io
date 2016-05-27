#include "header.hpp"
#include "server.hpp"
#include "DLog.h"
//#include "request.hpp"
//#include "Response.hpp"

namespace httpServer {

	Server::Server(boost::asio::io_service& io_service,
		const std::string& address, const std::string& port):
		ios(io_service)
	{
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(address, port);
		m_acceptor=make_shared<tcp::acceptor>(io_service, *resolver.resolve(query));
		logf << "listen on " << address << ":" << port << "\r\n";
	}


	void Server::startListen()
	{
		step(system::error_code(), 0);
	}

	// Enable the pseudo-keywords reenter, yield and fork.
#include <boost/asio/yield.hpp>

	void Server::step(system::error_code ec, std::size_t length)
	{
		if (!ec)
		{
			reenter(this)
			{
				// Loop to accept incoming connections.
				do
				{
					// Create a new socket for the next incoming connection.
					m_clientSocket = make_shared<tcp::socket>(ios);

					yield m_acceptor->async_accept(*m_clientSocket, bind(&Server::step,this,asio::placeholders::error,0));
					fork this->step(system::error_code(),0);

					// The parent continues looping to accept the next incoming connection.
					// The child exits the loop and processes the connection.
				} while (is_parent());
				logf << "accetClient from " << (*m_clientSocket).remote_endpoint();
/*				// Create the objects needed to receive a request on the connection.
				buffer_.reset(new boost::array<char, 8192>);
				request_.reset(new Request);

				// Loop until a complete request (or an invalid one) has been received.
				do
				{
					// Receive some more data. When control resumes at the following line,
					// the ec and length parameters reflect the result of the asynchronous
					// operation.
					yield socket_->async_read_some(boost::asio::buffer(*buffer_), *this);

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

				*/
			}
		}else{
			logf << "err:" << ec.message() << "\r\n";
		}
		// If an error occurs then the coroutine is not reentered. Consequently, no
		// new asynchronous operations are started. This means that all shared_ptr
		// references will disappear and the resources associated with the coroutine
		// will be destroyed automatically after this function call returns.
	}

	// Disable the pseudo-keywords reenter, yield and fork.
#include <boost/asio/unyield.hpp>

} // namespace httpServer
