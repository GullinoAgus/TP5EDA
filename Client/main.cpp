#include "client.h"

//Se pide un string o pedido de salida
int parseInput(string& input);

int main(void)
{
	CURLcode curlResult;  //Guearda el resultado del acceso a la direccion
	string input;	//Para guardar la direccion ingresada por consola
	while(parseInput(input))		//Mientras no llegue el comando de salida del programa continuamos con el funcionamiento
	{
		curlResult = clientconnection(input);	//Se conecta a la direccion ingresada
		switch (curlResult)
		{
		case CURLE_OK: 
			cout << endl << "All OK." << endl;
			break;
		case CURLE_URL_MALFORMAT:
			cout << endl << "Error ocurred: URL bad formating." << endl;
			break;
		case CURLE_COULDNT_CONNECT:
			cout << endl << "Error ocurred: Couldn't connect." << endl;
			break;
		case CURLE_COULDNT_RESOLVE_HOST:
			cout << endl << "Error ocurred: Couldn't resolve host." << endl;
			break;
		default:
			cout << endl << "Error ocurred: (General message) check host, availabitlity of server and URL." << endl;
			break;
		}
	}

	return 0;
}

int parseInput(string& input)
{
	string instring;
	cout << endl << "Ingrese la direccion a la que se desesa conectar en la forma host/path/filename , o Q para salir." << endl;
	cin >> instring;	//Se carga el string ingresado
	if (!instring.compare("Q") || !instring.compare("q"))		//Si es una q o Q salimos con 0, sino cargamos el mensaje en input
	{
		return 0;
	}
	input = instring;

	return 1;
}