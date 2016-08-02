#include "header.hpp"
#include "server.hpp"
#include "Setting.hpp"
#include <boost/xpressive/xpressive.hpp>
using namespace xpressive;

//#include "request.hpp"
//#include "Response.hpp"

Server::Server(asio::io_service& io_service) : ios(io_service)
{
	tcp::resolver resolver(io_service);
	tcp::resolver::query query(g_setting.getAddress(), g_setting.getPort());
	try
	{
		m_acceptor = make_shared<tcp::acceptor>(io_service, *resolver.resolve(query));
	}
	catch (system::system_error &e)
	{
		BOOST_LOG_TRIVIAL(error)<<"acceptor error " << e.what();
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
				m_connection = boost::make_shared<Connection>(*this);
				yield m_acceptor->async_accept(*m_connection->socket_, bind(&Server::startListen, this, _1));
				m_connection->run(system::error_code(), 0);
				//m_connection->start();
			} while (1);
		}
	}
	else {
		BOOST_LOG_TRIVIAL(error) << "listen error:" << ec.message();
	}
}

void Server::addFilter(char *match, FilterBasePtr filter)
{
	filterMap[std::string(match)]=filter;
}

bool Server::processFilter(shared_ptr<Request> req,shared_ptr<Response> res)
{
	auto filter_iter = filterMap.begin();
	auto filterMatch = false;
	while (filter_iter != filterMap.end())
	{
		auto regex = cregex::compile(filter_iter->first);
		if (regex_match(req->url.c_str(), regex)) {
			filter_iter->second->process(req, res);
			filterMatch = true;
		}
		filter_iter++;
	}
	return filterMatch;
}

#include <boost/asio/unyield.hpp>

