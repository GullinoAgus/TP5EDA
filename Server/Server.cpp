#include "Server.h"


Server::Server(boost::asio::io_context& _ioContext)
	:ioContext(_ioContext),
	acceptor(_ioContext, tcp::endpoint(tcp::v4(), PORTNUM))
{
	startListening();
}


void Server::startListening()
{

	Connection::pointer newConnection = Connection::createConnection(ioContext);

	acceptor.async_accept(newConnection->getSocket(),
		boost::bind(&Server::connectionHandler, this, newConnection, boost::asio::placeholders::error));

}


void Server::connectionHandler(Connection::pointer newConnection, const boost::system::error_code& error)
{
	
	if (!error)
	{
		newConnection->startHTTP(newConnection);
	}
	else
	{
		std::cerr << "err (recv): " << error.message() << std::endl;
	}
	std::cerr << "err (recv): " << error.message() << std::endl;
	this->startListening();
	
}