#include "curl/curl.h"
#include <iostream>
#include <stdio.h>
#include <string>

#define VERBOSE 1 //1 para mostrar todos los mensajes, 0 para no mostrarlos
#define CURLPORT 80

using namespace std;

void parseInput(string& input);
int parseCont(void);


int main(void)
{
	FILE* output = NULL;
	CURL* curl = curl_easy_init();
	CURLcode res;
	string input;

	fopen_s(&output, "response.txt", "w");

	if (curl && output) {
		do
		{
			parseInput(input);
			cout << "Starting cURL." << endl;
			curl_easy_setopt(curl, CURLOPT_URL, input.c_str());
			curl_easy_setopt(curl, CURLOPT_PORT, CURLPORT);
			curl_easy_setopt(curl, CURLOPT_VERBOSE, VERBOSE);
			curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTP);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, output);
			res = curl_easy_perform(curl);
			if (res)
			{
				cout << "Error ocurred when performing cURL." << endl;
			}
		} while (parseCont());
	}
	else
	{
		cout << "Couldn't init libcURL or open write file." << endl;
	}

	if (output)
	{
		fclose(output);
	}
	if (curl)
	{
		curl_easy_cleanup(curl);
	}
	return 0;
}

void parseInput(string& input)
{
	string instring;
	cout << "Ingrese la direccion a la que se desesa conectar en la forma host/path/filename." << endl;
	cin >> instring;
	input = instring;
}

int parseCont(void)	//Devuelve 0 si no se quiere continuar y 1 para continuar
{
	string contstring;
	cout << "\n\nQuiere conectarse a una nueva direccion?" << endl;
	cout << "Ingrese Y para ingresar una nueva direccion u otra cosa para salir del programa." << endl;
	cin >> contstring;
	if (!strcmp(contstring.c_str(), "Y"))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}