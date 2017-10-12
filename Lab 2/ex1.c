/*
	Write a program where you start a child process. Based on the parity of the child pid,
	the parent will send to the child a different message by writing it in a file. The
	child will read the message and will display it (e.g., if the child pid is even - "Good
	morning!", if it's odd - "Good night!"). The parent will wait the end of the child's
	execution.
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
	pid_t pid;
	int fd = open("result.txt", O_CREAT | O_RDWR);

	if((pid = fork() > 0) && (pid % 2 == 0)){
		write(fd, "Good morning!\n", 14);
	}
	else{
		if((pid % 2 != 0)){
			write(fd, "Good night!\n", 12);
		}
	}
}