/*
	Write a program that each 3 seconds displays the pid
	of the current process and a counter for this. When
	the process receives SIGUSR1 will write in a file the
	message: "I received a signal". The SIGINT signal will
	be ignored for the first 60 seconds of running the
	program, after that being handled implicitly.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void sighandler(int sig){
	int fd;

	if(sig == SIGUSR1){
		fd = open("Signals.txt", O_CREAT | O_RDWR);
		write(fd, "I received a signal\n", 20);
		close(fd);
	}
	else{
		if(sig == SIGINT){
			printf("SIGINT ignored");
		}
		else{
			if(sig == SIGINT){
				exit();
			}
		}
	}
}

int main(){
	for(int i = 0; ; i++){	//true
		signal(SIGUSR1, sighandler);
		if(i < 20){
			printf("SIGINT ignored");
		}

		printf("My process ID : %d\n", getpid());
		printf("Counter : %d\n", i + 1);
		printf("---------------------\n");
		sleep(3);
	}
}