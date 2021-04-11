#pragma once

#include <iostream>

#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>


using boost::asio::ip::tcp;

class Connection : public boost::enable_shared_from_this<Connection>
{
public:
	typedef boost::shared_ptr<Connection> pointer;

	static pointer createConnection(boost::asio::io_context& ioContext);

	tcp::socket& getSocket();

	Connection(boost::asio::io_context& ioContext);

	int readData(std::string& buffer);

	void sendData(std::string& buffer);

private:
	
	tcp::socket conSocket;

};

