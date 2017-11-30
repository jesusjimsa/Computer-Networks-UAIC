/*
	Adapt exercise 1 from the previous lab to the concurrent server model.
	Modify the solution such that the response to be sent to the server
	also as a structure, defined as following:

	struct response{
		char message[30];
		int result;
	}
	
	The message field will normally include as a response message "The
	result is:", and the result field will contain the result of the
	operation computed by the server. The server will get "tired" at each
	third client and will send as response the message "I am tired. Try
	another time.", without calculating anymore the operation result (the
	field is set to 0). 
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
#include <signal.h>

/* el puerto usado */
#define PORT 2024

/* el código de error devuelto por ciertas llamadas */
extern int errno;

struct Operation{
	int number1;	//value 1
	int number2;	//value 2
	char op;		//opcode - '+','-','*' or '/'
};

struct response{
	char message[30];
	int result;
};

int main(){
	struct sockaddr_in server;	// la estructura utilizada por el servidor
	struct sockaddr_in from;
	struct Operation mensaje;
	//char msg[100];		//mensaje recibido del cliente
	//char msgrasp[100]=" ";        //mensaje de respuesta del cliente
	const char *STD_ANS = "The result is:";	//Respuesta estandar para cuando consigue resolver la operación
	const char *STD_TIRED = "I am tired. Try another time.";	//Respuesta estandar para cuando no puede soportar más clientes
	int sd;			//descriptor de socket
	int clients_rnow = 0;	//Clients at the moment

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
		pid_t pid; //pid2, pid3;

		printf("[server]Estamos esperando el puerto %d...\n", PORT);
		fflush(stdout);

		/* aceptamos un cliente (estado de bloqueo hasta que se establezca la conexión) */
		client = accept(sd, (struct sockaddr *) &from, &length);

		clients_rnow++;

		/* error al aceptar una conexión de un cliente */
		if (client < 0){
			perror ("[server]Error en accept().\n");
			continue;
		}

		if(clients_rnow <= 3){
			if((pid = fork()) == 0){		//Hijo
				int result;
				struct response answer;
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
				//bzero(msgrasp, 100);
				//sprintf(msgrasp, "%d", result);
				strncpy(answer.message, STD_ANS, 15);
				answer.result = result;

				//printf("[server]Enviamos el mensaje...%s\n", msgrasp);
				printf("[server]Enviamos el mensaje...\n");

				/* devolvemos el mensaje del cliente */
				if (write (client, &answer, 100) <= 0){
					perror ("[server]Error en write() con client.\n");
					continue;		/* seguimos escuchando */
				}
				else{
					printf ("[server]Mensaje enviado con éxito.\n");
				}
				
				/* terminamos con este cliente, cerramos la conexión */
				close (client);

				/* además de cerrar la conexión cortamos la ejecución del hijo */
				//kill(pid, SIGKILL);
				
				/* disminuimos el número de clientes activos */
				clients_rnow--;
			}
			else{
				printf("Soy el papi\n");
			}
		}
		else{	//Too many clients
			struct response answer;
			
			strncpy(answer.message, STD_TIRED, 30);
			answer.result = 0;

			/* devolvemos el mensaje del cliente */
			if (write (client, &answer, 100) <= 0){
				perror ("[server]Error en write() con client.\n");
				continue;		/* seguimos escuchando */
			}
			else{
				printf ("[server]Mensaje enviado con éxito.\n");
			}

			/* terminamos con este cliente, cerramos la conexión */
			close (client);

			clients_rnow--;
		}
	}				/* while */

	free(STD_ANS);
	free(STD_TIRED);
}				/* main */
