/*
	Write a program similar to the given exec example that will execute
	another command (e.g.,: cat) by using the function execl.
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	pid_t pid;			/* PID-ul procesului copil */
	int status;			/* starea de terminare a procesului copil */

	printf ("Let's execute this command...\n");

	if ((pid = fork ()) < 0){
	  perror ("fork()");
	  exit (1);
	}
	else
		if (pid){			/* parinte */
			if (wait (&status) < 0){
				perror ("wait()");
			}
			
			printf ("Command executed.\n");
			
			exit (0);
	}
	else{				/* fiu */
		/* vom folosi execlp() */
		execlp ("cat", "cat", "result.txt", NULL);
		
		/* daca ajungem aici inseamna ca nu s-a putut executa */
		printf ("Execution error!\n");
		
		exit (1);
	}
}