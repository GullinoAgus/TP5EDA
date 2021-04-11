#include "HTTP.h"

#include <ctime>
#include <iostream>
#include <string>

string write_ok_message() {

    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    ctime_s(datas, 1024, &now);
    return std::string(datas);

}

void write_error_message() {

    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    ctime_s(datas, 1024, &now);
    return std::string(datas);

}