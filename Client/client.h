#ifndef CLIENT_H
#define CLIENT_H

#include "curl/curl.h"
#include <iostream>
#include <stdio.h>
#include <string>

#ifdef DEBUG
#define VERBOSE 1 //Valor en 1 para mostrar todos los mensajes, 0 para no mostrarlos
#else //!DEBUG
#define VERBOSE 0
#endif

#define CURLPORT 80	//Puerto al que se conecta

using namespace std;

//Recibe una direccion y se conecta a ella
//Carga la respuesta en un archivo
CURLcode clientconnection(string&);


#endif // !CLIENT_H

