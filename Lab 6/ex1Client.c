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
	CLIENT
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>

/* el código de error devuelto por ciertas llamadas */
extern int errno;

/* puerto de acceso al servidor */
int port;

// Estructura que guardará los datos a enviar
struct Operation{
	int number1;	//value 1
	int number2;	//value 2
	char op;		//opcode - '+','-','*' or '/'
};

int main(int argc, char *argv[]){
	int sd;			// descriptor de socket
	struct sockaddr_in server;	// la estructura utilizada para conectar
	char msg[100];		// mensaje enviado
	struct Operation mensaje;

	/* ¿Están todos los argumentos en la línea de comandos? */
	if(argc != 3){
      printf ("Sintaxis: %s <server_name> <port>\n", argv[0]);
      return -1;
    }

	/* armamos el puerto */
	port = atoi (argv[2]);

	/* creación del socket */
	if((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1){
		perror ("Error de socket().\n");
		return errno;
    }

	/* llenamos la estructura utilizada para conectar al servidor */
	/* la familia de socket */
	server.sin_family = AF_INET;
	
	/* dirección IP del servidor */
	server.sin_addr.s_addr = inet_addr(argv[1]);
	
	/* el puerto de conexión */
	server.sin_port = htons(port);

	/* nos conectamos al servidor */
	if(connect(sd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1){
		perror ("[client]Error en connect().\n");
		return errno;
    }

	/* leyendo el mensaje */
	//bzero(msg, 100);	// Esta función coloca 100 bytes a 0 en msg
	printf("[client]Por favor ingrese un numero: ");
	fflush(stdout);		// Obliga al ordenador a imprimir por pantalla, en lugar de mandarlo a un buffer hasta que haya hueco
	read(0, &mensaje.number1, sizeof(int));

	printf("[client]Por favor ingrese otro numero: ");
	fflush(stdout);
	read(0, &mensaje.number2, sizeof(int));

	printf("[client]Por favor ingrese una operación (+, -, *  o  /): ");
	fflush(stdout);
	read(0, &mensaje.op, sizeof(char));

	/* enviando el mensaje al servidor */
	if(write (sd, &mensaje, sizeof(mensaje)) <= 0){
		perror ("[client]Error al escribir en el servidor.\n");
		return errno;
    }

	/* leyendo la respuesta del servidor (bloqueador de llamadas hasta que el servidor responda) */
	if(read(sd, msg, 100) < 0){
 		perror ("[client]Error en read() del servidor.\n");
		return errno;
    }
	
	/* mostrar el mensaje recibido */
	printf("[client]El resultado de la operacion recibido es: %s\n", msg);

	/* cerramos la conexión, hemos terminado */
	close(sd);
}
