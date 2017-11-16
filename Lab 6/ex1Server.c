/*
	Write a client and a TCP server following the steps described in the lab, where:
		- the client sends two numbers and an operation code ('+', '-', '*', '/') to the server, and receives the result
		- the request will be sent as a structure including the necessary fields, defined as following: 
			struct operation{
				int number1;	//value 1
				int number2;	//value 2
				char op;		//opcode - '+','-','*' or '/'
			};

		- the server receives the request structure, computes the result and returns it to the client as an integer
*/

/*
	SERVER
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

/* el puerto usado */
#define PORT 2024

/* el código de error devuelto por ciertas llamadas */
extern int errno;

struct Operation{
	int number1;	//value 1
	int number2;	//value 2
	char op;		//opcode - '+','-','*' or '/'
};

int main(){
	struct sockaddr_in server;	// la estructura utilizada por el servidor
	struct sockaddr_in from;
	//char msg[100];		//mensaje recibido del cliente
	char msgrasp[100]=" ";        //mensaje de respuesta del cliente
	int sd;			//descriptor de socket
	struct Operation mensaje;
	int result;

	/* creando un socket */
	if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1){
		perror("[server]Error de socket().\n");
		return errno;
	}

	/* preparación de estructuras de datos */
	bzero(&server, sizeof (server));
	bzero(&from, sizeof (from));

	/* llene la estructura utilizada por el servidor */
	/* estableciendo la familia de sockets */
	server.sin_family = AF_INET;
	
	/* aceptamos cualquier dirección */
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	
	/* usamos un puerto de usuario */
	server.sin_port = htons(PORT);

	/* adjuntamos el socket */
	if (bind(sd, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1){
		perror("[server]Error en bind().\n");
		return errno;
	}

	/* le pedimos al servidor que escuche si los clientes vienen a conectarse */
	if (listen (sd, 5) == -1){
		perror ("[server]Error de listen().\n");
		return errno;
	}

	/* servimos a nuestros clientes iterativamente... */
	while (1){
		int client;
		socklen_t length = sizeof(from);

		printf("[server]Estamos esperando el puerto %d...\n", PORT);
		fflush(stdout);

		/* aceptamos un cliente (estado de bloqueo hasta que se establezca la conexión) */
		client = accept(sd, (struct sockaddr *) &from, &length);

		/* error al aceptar una conexión de un cliente */
		if (client < 0){
			perror ("[server]Error en accept().\n");
			continue;
		}

		/* se estableció la conexión, se espera el mensaje */
		//bzero(msg, 100);
		printf("[server]Esperamos el mensaje...\n");
		fflush(stdout);

		/* leyendo el mensaje */
		if (read(client, &mensaje, sizeof(mensaje)) <= 0){
			perror("[server]Error en read() del client.\n");
			close(client);	/* cerramos la conexión con el cliente */
			continue;		/* seguimos escuchando */
		}

		printf("[server]Mensaje recibido...\n");

		/* Procedemos a realizar los cálculos */
		switch(mensaje.op){
			case '+':
				result = mensaje.number1 + mensaje.number2;
				break;
			case '-':
				result = mensaje.number1 - mensaje.number2;
				break;
			case '*':
				result = mensaje.number1 * mensaje.number2;
				break;
			case '/':
				result = mensaje.number1 / mensaje.number2;
				break;
			default:
				result = INT_MAX;	//No se ha enviado una operación válida
				break;
		}

		/* preparamos el mensaje de respuesta */
		bzero(msgrasp, 100);
		sprintf(msgrasp, "%d", result);

		printf("[server]Enviamos el mensaje...%s\n", msgrasp);

		/* devolvemos el mensaje del cliente */
		if (write (client, msgrasp, 100) <= 0){
			perror ("[server]Error en write() con client.\n");
			continue;		/* seguimos escuchando */
		}
	  	else{
			printf ("[server]Mensaje enviado con éxito.\n");
		}
		
		/* terminamos con este cliente, cerramos la conexión */
		close (client);
	}				/* while */
}				/* main */
