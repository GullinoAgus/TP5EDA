//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <ctime>
#include <iostream>
#include <string>
#include "Server.h"

using boost::asio::ip::tcp;
char datas[1024];
std::string make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    ctime_s(datas, 1024, &now);
    return std::string(datas);
}




class tcp_connection
    : public boost::enable_shared_from_this<tcp_connection>
{
public:
    typedef boost::shared_ptr<tcp_connection> pointer;

    static pointer create(boost::asio::io_context& io_context)
    {
        return pointer(new tcp_connection(io_context));
    }

    tcp::socket& socket()
    {
        return socket_;
    }

    void start()
    {
        message_ = make_daytime_string();

        boost::asio::async_write(socket_, boost::asio::buffer(message_),
            boost::bind(&tcp_connection::handle_write, shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }

private:
    tcp_connection(boost::asio::io_context& io_context)
        : socket_(io_context)
    {
    }

    void handle_write(const boost::system::error_code& /*error*/,
        size_t /*bytes_transferred*/)
    {
    }

    tcp::socket socket_;
    std::string message_;
};

class tcp_server
{
public:
    tcp_server(boost::asio::io_context& io_context)
        : io_context_(io_context),
        acceptor_(io_context, tcp::endpoint(tcp::v4(), 45575))
    {
        
        start_accept();
    }

    static void handle_read(const boost::system::error_code& err,
        size_t bytes_transferred, tcp_connection::pointer Connection, char data[1024])
    {
        if (!err) {
            std::cout << data << std::endl;
            Connection->socket().async_read_some(
                boost::asio::buffer(data, 1024),
                boost::bind(&handle_read,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred,
                    Connection,
                    data));
        }
        else {
            std::cerr << "err (recv): " << err.message() << std::endl;       }
    }

private:
    void start_accept()
    {
        tcp_connection::pointer new_connection =
            tcp_connection::create(io_context_);

        acceptor_.async_accept(new_connection->socket(),
            boost::bind(&tcp_server::handle_accept, this, new_connection,
                boost::asio::placeholders::error));
    }



    void handle_accept(tcp_connection::pointer newConnection,
        const boost::system::error_code& error)
    {
        char data[1024];
        if (!error)
        {

            newConnection->socket().async_read_some(
                boost::asio::buffer(data, 1024),
                boost::bind(&handle_read,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred,
                    newConnection,
                    data));
            newConnection->start();

        }
        std::cerr << "err (recv): " << error.message() << std::endl;
        start_accept();
    }

    boost::asio::io_context& io_context_;
    tcp::acceptor acceptor_;
};

int main()
{
    try
    {
        boost::asio::io_context io_context;
        tcp_server server(io_context);
        io_context.run();

    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}