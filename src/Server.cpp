#include "header.hpp"
#include "server.hpp"
#include "Setting.hpp"
//#include "request.hpp"
//#include "Response.hpp"

	Server::Server(boost::asio::io_service& io_service): ios(io_service)
	{
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(g_setting.getAddress(), g_setting.getPort());
		try
		{
			m_acceptor = make_shared<tcp::acceptor>(io_service, *resolver.resolve(query));
		}
		catch (system::system_error &e)
		{
			logf << e.what()<< "\r\n";
		}
	}

#include <boost/asio/yield.hpp>
	void Server::startListen(system::error_code ec)
	{
		if (!ec)
		{
			reenter(this)
			{
				do
				{
					m_connection = boost::make_shared<Connection>(ios,g_setting.getRoot());
					yield m_acceptor->async_accept(m_connection->m_socket, bind(&Server::startListen, this, _1));
					m_connection->run(system::error_code(),0);
				} while (1);
			}
		}
		else {
			logf << "error:"<<ec.message()<<"\r\n";
		}
	}
#include <boost/asio/unyield.hpp>

