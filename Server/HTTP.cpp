#include "HTTP.h"

#include <ctime>
#include <iostream>
#include <string>

using namespace std;

//  HACER UN PARSER PARA LO QUE RECIBIMOS (CHECKEAR QUE EL HOST ES MI IP) - el path - que termine en 2 CLRF, etc
//  
//  ENTRAR AL /PATH/FILENAME para devolver filenameLength y filenameContent
//  

string write_ok_message() {

    char buffer[100];
    int i = 0;

    string message = string("HTTP/1.1 200 OK Date: ");

    time_t time_written = time(0);
    ctime_s(buffer, 100, &time_written);

    while (buffer[i] != '\0') {

        message.push_back(buffer[i]);
        i++;
    }

    message += string("Location: 127.0.0.1/path/filename Cache - Control: max - age = 30 Expires : ");

    time_written += 30;
    time_written = time(0);
    ctime_s(buffer, 100, &time_written);

    i = 0;

    while (buffer[i] != '\0') {

        message.push_back(buffer[i]);
        i++;
    }

    message += string("Content - Length: filenameLength Content - Type : text / html; charset = iso - 8859 - 1 filenameContent");

    return message;
}

string write_error_message() {

    char buffer[100];
    int i = 0;

    string message = string("HTTP / 1.1 404 Not Found Date : ");

    time_t time_written = time(0);
    ctime_s(buffer, 100, &time_written);

    while (buffer[i] != '\0') {

        message.push_back(buffer[i]);
        i++;
    }

    message += string("Cache-Control: public, max-age=30 Expires: ");

    time_written += 30;
    time_written = time(0);
    ctime_s(buffer, 100, &time_written);

    i = 0;

    while (buffer[i] != '\0') {

        message.push_back(buffer[i]);
        i++;
    }

    message += string("Content-Length: 0 Content - Type: text / html; charset = iso - 8859 - 1 ");

    return message;
}