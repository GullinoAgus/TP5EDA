#include "Connection.h"


Connection::~Connection()
{
#ifdef DEBUG
	std::cerr << "Connection closed." << std::endl;
#endif // DEBUG
}

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

		elaborateMessage();	//Parseo la entrada de datos y creo una respuesta en toSendMesage

		boost::asio::async_write(this->conSocket, boost::asio::dynamic_buffer(this->toSendMsg),
			boost::bind(&Connection::sendDataHandler, this,
				boost::asio::placeholders::bytes_transferred, thisCon, boost::asio::placeholders::error));

#ifdef DEBUGHTTP
		std::cout << "Received request:" << std::endl << this->receivedMsg << std::endl << std::endl;
		std::cout << "Sent response:" << std::endl << this->toSendMsg << std::endl;
#endif // DEBUGHTTP
		this->receivedMsg = "";

	}
	else
	{
		std::cerr << error.message() << std::endl;
	}
	
}


void Connection::sendDataHandler(int sentBytes, Connection::pointer thisCon, const boost::system::error_code& error)
{
	if (error)
	{
#ifdef DEBUG
		std::cerr << "Error ocurred while writting: " << error.message() << std::endl;
#endif // DEBUG
	}

	this->conSocket.close();
}
