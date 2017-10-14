/* sig.c

   Muestra el contenido del archivo "/ etc / services" cuando aparece
    la señal SIGUSR2

   Autor: Sabin-Corneliu Buraga <busaco@infoiasi.ro> (c)1998-2001
   Ultima actualizare: 10 iulie 2001
*/
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <stdlib.h>

void sighandler (int sig){		/* función de procesamiento de señal*/
	pid_t pid;

	if ((pid = fork ()) < 0){	/* ejecutamos 'less' como un proceso secundario */
		perror ("fork()");
		exit (1);
	}
	if (!pid){			/* hijo */
		execl ("/usr/bin/less", "less", "/etc/services", NULL);
		perror ("exec()");
		exit (1);
	}
	else{				/* padre */
		if (wait (NULL) < 0){
			perror ("wait()");
		}
	}
}

int main (){	/* programa principal */
	/* adjuntamos la función de tratamiento a la señal SIGUSR2 */
	if (signal (SIGUSR2, sighandler) == SIG_ERR){
		perror ("signal()");
		return 1;
	}
	
	/* estamos esperando que aparezca una señal */
	pause ();
	
	return 0;
}