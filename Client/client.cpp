#include  "client.h"

CURLcode clientconnection(string& input)
{
	FILE* output = NULL;	//Crea el puntero al archivo para guardar la respuesta del server
	CURL* curl = curl_easy_init();	//Inicializa la libreria curl y creo el handler
	CURLcode res;	//Resultado de hacer el curl

	if (curl) {	//Si se pudo iniciar bien curl
		fopen_s(&output, "response.txt", "w");	//Abre el archivo a escribir
		if (output) {	//Si se pudo abrir bien el archivo
			cout << "Starting cURL." << endl;
			curl_easy_setopt(curl, CURLOPT_URL, input.c_str());	//Carga todas las opciones para curl
			curl_easy_setopt(curl, CURLOPT_PORT, CURLPORT);
			curl_easy_setopt(curl, CURLOPT_VERBOSE, VERBOSE);
			curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTP);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, output);
			res = curl_easy_perform(curl);	//Se hace el GET
			fclose(output);	//Se cierra el archivo cargado
		}
		else	//Si no se pudo abrir el archivo avisa al usuario
		{
			cout << endl << "Error opening file." << endl;
		}
		curl_easy_cleanup(curl);	//Libera el handler de curl
	}
	else	//Si no se pudo inicializar libcurl avisa al usuario
	{
		cout << endl << "Couldn't init libcURL." << endl;
	}

	return res;
}