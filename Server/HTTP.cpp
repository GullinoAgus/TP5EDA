#include "HTTP.h"

#include <ctime>

#include <string>

using namespace std;

void HTTP:: elaborateMessage() {

    int error = 0;  //Detecta cuando es momento de enviar el mensaje de error

    string auxString; //String auxiliar con el que realizare los recortes
    int auxPositionINICIAL = 0;
    int auxPositionFINAL;

    auxPositionFINAL = receivedMsg.find_first_of(' ', 0 );   //Busco el primer espacio desde el inicio del string

    auxString = receivedMsg.substr(auxPositionINICIAL, auxPositionFINAL);

    if (!error) {   //LECTURA DE COMANDOS
        
        if (!auxString.compare(string("GET"))) {    //Si el comando ingresado es GET...

            write_GET_message();
        }
        else if (!auxString.compare(string("VIVA-PERON"))) {    //Si el comando ingresado es VIVA-PERON...


        }
        else {
            error = 1;
            write_error_message();
        }
    }

    auxPositionINICIAL = auxPositionFINAL + 1;

    auxPositionFINAL = receivedMsg.find_first_of(' ', auxPositionFINAL + 1);   

    auxString = receivedMsg.substr(auxPositionINICIAL, auxPositionFINAL);

    if (!error) {   //LECTURA DEL PATH

            //EN AUXSTRING ESTA EL PATH. LEELO
    }

    auxPositionINICIAL = auxPositionFINAL + 1;

    auxPositionFINAL = receivedMsg.find_first_of(1310, auxPositionFINAL + 1); //OJO, PORQUE ENGANCHO UN ' ' TAMBIEN
                                                                               //CON 1310 estaria chequeando el \r\n, ver si funca

    auxString = receivedMsg.substr(auxPositionINICIAL, auxPositionFINAL - 1);

    if (!error) {   //LECTURA DEL PATH

            //EN AUXSTRING ESTA LA VERSION DE HTML si pinta hacer algo
    }

    auxPositionINICIAL = auxPositionFINAL + 2; //Me muevo al siguiente renglon

    auxPositionFINAL = receivedMsg.find_first_of(' ', auxPositionFINAL );

    auxString = receivedMsg.substr(auxPositionINICIAL, auxPositionFINAL );

    if (!error) {

        if (!auxString.compare(string("host:")) || !auxString.compare(string("Host:"))) {    //Si se ingreso host: o Host:

            auxPositionINICIAL = auxPositionFINAL + 1;

            auxPositionFINAL = receivedMsg.find_first_of(1310, auxPositionFINAL + 1);

            auxString = receivedMsg.substr(auxPositionINICIAL, auxPositionFINAL -1);    //quito el ' ' del final tambien

            //en AUXString esta escrito el host:
        }
    }

    auxPositionINICIAL = auxPositionFINAL + 2; //Me muevo al siguiente renglon

    auxPositionFINAL = receivedMsg.find_first_of(13101310, auxPositionFINAL);   //Busco el \r\n\r\n

    if (auxPositionFINAL == -1) {   //no encontro el \r\n\r\n

        error = 1;
        write_error_message();
    }

    auxString = receivedMsg.substr(auxPositionINICIAL, auxPositionFINAL); //ACA ESTA EL RESTO DEL STRING, si sirve de algo
}


void HTTP::write_GET_message() {

    char buffer[100];
    int i = 0;

    string message = string("HTTP/1.1 200 OK \r\nDate: ");
    message.erase(message.length(), message.length()); //Borro el '\0' del final del string 

    time_t time_written = time(0);
    ctime_s(buffer, 100, &time_written);

    while (buffer[i] != '\0') {

        message.push_back(buffer[i]);
        i++;
    }

    message += string("Location: 127.0.0.1/path/filename \r\nCache - Control: max - age = 30 \r\nExpires : ");
    message.erase(message.length(), message.length()); //Borro el '\0\ del final del string 

    time_written += 30;
    time_written = time(0);
    ctime_s(buffer, 100, &time_written);

    i = 0;

    while (buffer[i] != '\0') {

        message.push_back(buffer[i]);
        i++;
    }

    message += string("\r\nContent - Length: filenameLength \r\nContent - Type : text / html; charset = iso - 8859 - 1 filenameContent\r\n\r\n");
    message.erase(message.length(), message.length()); //Borro el '\0\ del final del string 

    toSendMsg = message;
}

void HTTP::write_error_message() {

    char buffer[100];
    int i = 0;

    string message = string("HTTP / 1.1 404 Not Found \r\nDate : ");
    message.erase(message.length(), message.length()); //Borro el '\0\ del final del string  

    time_t time_written = time(0);
    ctime_s(buffer, 100, &time_written);

    while (buffer[i] != '\0') {

        message.push_back(buffer[i]);
        i++;
    }

    message += string("Cache-Control: public, max-age=30 \r\nExpires: ");
    message.erase(message.length(), message.length()); //Borro el '\0\ del final del string  

    time_written += 30;
    ctime_s(buffer, 100, &time_written);

    i = 0;

    while (buffer[i] != '\0') {

        message.push_back(buffer[i]);
        i++;
    }

    message += string("Content-Length: 0 \r\nContent - Type: text / html; charset = iso - 8859 - 1 \r\n\r\n");

    toSendMsg = message;
}