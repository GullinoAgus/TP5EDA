#ifndef CLIENT_H
#define CLIENT_H

#include "curl/curl.h"
#include <iostream>
#include <stdio.h>
#include <string>

#define VERBOSE 1 //Valor en 1 para mostrar todos los mensajes, 0 para no mostrarlos
#define CURLPORT 80	//Puerto al que se conecta

using namespace std;

//Recibe una direccion y se conecta a ella
//Carga la respuesta en un archivo
void clientconnection(string&);


#endif // !CLIENT_H

