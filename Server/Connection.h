#pragma once

#include <iostream>

#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "HTTP.h"

using boost::asio::ip::tcp;

class Connection : public boost::enable_shared_from_this<Connection>, public HTTP
{
public:
	typedef boost::shared_ptr<Connection> pointer;

	static pointer createConnection(boost::asio::io_context& ioContext);

	tcp::socket& getSocket();

	Connection(boost::asio::io_context& ioContext);

	void startHTTP(Connection::pointer thisCon);

private:
	void readDataHandler(int recievedBytes, Connection::pointer thisCon, const boost::system::error_code& error);

	void sendDataHandler(const boost::system::error_code& error);
	tcp::socket conSocket;

};

