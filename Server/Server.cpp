#include "Server.h"


Server::Server(boost::asio::io_context& _ioContext)
	:ioContext(_ioContext),
	acceptor(_ioContext, tcp::endpoint(tcp::v4(), 45575))
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
	this->startListening();
	if (!error)
	{
		int read = 0;
		while (read != -1) {
			std::string buffer;
			read = newConnection->readData(buffer);
			if (read > 0)
			{
				std::cout << read << std::endl;
				std::cout << buffer << std::endl;
				newConnection->sendData(buffer);
			}
			
		}
	}
	std::cerr << "err (recv): " << error.message() << std::endl;

	
}