/*
	Please write a program that instantiates a child process and will
	use pipes for communicating in the following scenario:
	- the parent writes a number in the pipe
	- the child checks a property of the number (e.g.,: if it is odd
	  or even) and will send to the parent the answer through the pipe (yes, no)
	- the parent will display the received answer
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

int main(){
	int pdp[2], pdc[2];
	int random;
	pid_t pid;

	char bufnum[4];
	char bufans[1024];
	int num;

	srand(time(NULL));

	if (pipe(pdp) == -1){
		fprintf(stderr, "Pipe father\n");
		exit(1);
	}

	if (pipe(pdc) == -1){
		fprintf(stderr, "Pipe child\n");
		exit(1);
	}

	switch(pid = fork()){
		case -1:
			perror("fork");
			exit(1);
			break;
		case 0:		//Hijo
			read(pdp[0], bufnum, strlen(bufnum));
			num = atoi(bufnum);

			printf("jej %s\n", bufnum);

			if(num % 2 == 0){
				strncpy(bufans, "yes", 3);
			}
			else{
				strncpy(bufans, "no", 2);
			}

			printf("je%s\n", bufans);

			write(pdc[1], bufans, strlen(bufans));

			break;
		default:	//Padre
			random = rand() % 1000;
			sprintf(bufnum, "%d", random);
			
			write(pdp[1], bufnum, strlen(bufnum));
			printf("%d has been sent\n", random);

			read(pdc[0], bufans, strlen(bufans));
			printf("Is %d an even number?\nThe answer is %c\n", random, *bufans);

			break;
	}

	kill(pid, SIGKILL);
	close(pdp[0]);
	close(pdp[1]);
	close(pdc[0]);
	close(pdc[1]);
}