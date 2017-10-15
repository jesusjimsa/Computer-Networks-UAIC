/*
	Write a program that starts three child processes. The parent
	process does not end before the children are ending. The first
	child process should execute the ps command. The second child
	process should display its own id and end with an exit code
	greater than 0. The third process should send a SIGUSR signal
	to the parent that should be handled by the parent using
	sigaction by displaying a message. The parent process will
	display the exit codes for each of the three processes.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

int main(){
	pid_t pid1, pid2, pid3, pidf;

	for(int i = 0; i < 3; i++){
		if(fork() == 0){
			switch(i){
				case 0:
					execlp ("ps", "ps", NULL);
					break;
				case 1:
					pid1 = getppid();
					printf("\nThe second child's id is: %d\n", pid1);
					kill(pid1, SIGKILL);
					printf("Muerto morio\n");
					break;
				case 2:
					printf("jeje\n");
					break;
			}
		}
	}

	printf("Pues sí que sale\n");

	//wait();
}