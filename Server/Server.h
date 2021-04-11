#pragma once
#include "Connection.h"

class Server
{
public:

	Server(boost::asio::io_context& _ioContext);

private:

	void startListening();

	void connectionHandler(Connection::pointer newConnection, const boost::system::error_code& error);


	boost::asio::io_context& ioContext;
	tcp::acceptor acceptor;
};

