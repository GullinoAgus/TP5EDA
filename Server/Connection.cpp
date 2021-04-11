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


void Connection::startHTTP(Connection::pointer thisCon)
{
		boost::asio::async_read_until(this->conSocket, boost::asio::dynamic_buffer(this->receivedMsg), "\r\n\r\n",
			boost::bind(&Connection::readDataHandler, this,
				boost::asio::placeholders::bytes_transferred, thisCon, boost::asio::placeholders::error ));

}


void Connection::readDataHandler( int recievedBytes, Connection::pointer thisCon, const boost::system::error_code& error)
{
	if (!error)
	{
		std::cout << recievedBytes << std::endl;
		std::cout << this->receivedMsg << std::endl;
		if (this->receivedMsg == std::string("quit\r\n\r\n"))
		{
			return;
		}
		this->receivedMsg = "";
		startHTTP(thisCon);
	}
	else
	{
		std::cerr << error.message() << std::endl;
	}
	
}


void Connection::sendDataHandler(const boost::system::error_code& error)
{
	try
	{
		boost::asio::write(this->getSocket(), boost::asio::dynamic_buffer(this->toSendMsg));
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
