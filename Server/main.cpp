

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

int main()
{

    try
    {
        boost::asio::io_context io_context;
        Server server(io_context);
        io_context.run();

    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}