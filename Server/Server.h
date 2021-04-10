#pragma once
#include "Connection.h"

class Server
{
public:

	Server(boost::asio::io_context& ioContext);

private:

	void startListening();

	//void connectionHandler(Connection::pointer newConnection);


	boost::asio::io_context& ioContext;
	tcp::acceptor _acceptor;
};

