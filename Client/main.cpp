#include "client.h"

//Carga en input el string ingresado por consola
void parseInput(string& input);
//Pregunta si se desea ingresar una nueva direccion,
//devuelve 1 para continuar, 0 para terminar el programa
int parseCont(void);

int main(void)
{
	string input;	//Para guardar la direccion ingresada por consola
	do
	{
		parseInput(input);	//Carga el host/path/filename
		clientconnection(input);	//Se conecta a la direccion ingresada
	}
	while (parseCont());	//Pregunta si se desea cargar una nueva direccion
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