#include "curl/curl.h"
#include <iostream>
#include <stdio.h>
#include <string>

#define VERBOSE 1 //Valor en 1 para mostrar todos los mensajes, 0 para no mostrarlos
#define CURLPORT 80	//Puerto al que se conecta

using namespace std;

//Carga en input el string ingresado por consola
void parseInput(string& input);
//Pregunta si se desea ingresar una nueva direccion,
//devuelve 1 para continuar, 0 para terminar el programa
int parseCont(void);


int main(void)
{
	FILE* output = NULL;	//Crea el puntero al archivo para guardar la respuesta del server
	CURL* curl = curl_easy_init();	//Inicializa la libreria curl y creo el handler
	CURLcode res;	//Resultado de hacer el curl
	string input;	//La direccion ingresada por consola

	if (curl) {	//Si se pudo iniciar bien curl
		do
		{
			fopen_s(&output, "response.txt", "w");	//Abre el archivo a escribir
			if (output) {	//Si se pudo abrir bien el archivo
				parseInput(input);	//Carga el host/path/filename
				cout << "Starting cURL." << endl;
				curl_easy_setopt(curl, CURLOPT_URL, input.c_str());	//Carga todas las opciones para curl
				curl_easy_setopt(curl, CURLOPT_PORT, CURLPORT);
				curl_easy_setopt(curl, CURLOPT_VERBOSE, VERBOSE);
				curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTP);
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, output);
				res = curl_easy_perform(curl);	//Se hace el GET
				if (res)	//Si devuelve un error avisa al usuario
				{
					cout << "Error ocurred when performing cURL." << endl;
				}
				fclose(output);	//Se cierra el archivo cargado
			}
			else	//Si no se pudo abrir el archivo avisa al usuario
			{
				cout << "Error opening file." << endl;
			}
		} while (parseCont());	//Pregunta si se desea cargar una nueva direccion
		curl_easy_cleanup(curl);	//Libera el handler de curl
	}
	else	//Si no se pudo inicializar libcurl avisa al usuario
	{
		cout << "Couldn't init libcURL." << endl;
	}
	return 0;
}

void parseInput(string& input)
{
	string instring;
	cout << "Ingrese la direccion a la que se desesa conectar en la forma host/path/filename." << endl;
	cin >> instring;	//Se carga el string ingresado
	input = instring;
}

int parseCont(void)	//Devuelve 0 si no se quiere continuar y 1 para continuar
{
	string contstring;
	cout << "\n\nQuiere conectarse a una nueva direccion?" << endl;
	cout << "Ingrese Y para ingresar una nueva direccion u otra cosa para salir del programa." << endl;
	cin >> contstring;	//Se carga el string ingresado
	if (!strcmp(contstring.c_str(), "Y"))	//Si es la tecla Y devuelve 1 para continuar, sino devuelve 0
	{
		return 1;
	}
	else
	{
		return 0;
	}
}