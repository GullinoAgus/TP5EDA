#include "Connection.h"


Connection::Connection(boost::asio::io_context& ioContext)
	: conSocket(ioContext)
{
}


Connection::pointer Connection::createConnection(boost::asio::io_context& ioContext)
{
	return Connection::pointer(new Connection(ioContext));
}


tcp::socket& Connection::getSocket()
{
	return conSocket;
}


int Connection::readData(std::string& buffer)
{
	int recievedBytes = 0;

	try 
	{
		recievedBytes = boost::asio::read_until(this->getSocket(), boost::asio::dynamic_buffer(buffer), "\r\n\r\n");
	}
	catch(std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		recievedBytes = -1;
	}
	return recievedBytes;
}


void Connection::sendData(std::string& buffer)
{
	try
	{
		boost::asio::write(this->getSocket(), boost::asio::dynamic_buffer(buffer));
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
