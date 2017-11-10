/* 
	Write a program that receives as input argument a file name
	or a directory and returns the type of the corresponding
	disk entry (file or directory) and the time of when the last
	changes were done (hint: fstat).
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]){
	if(argc < 2){
		perror("Incorrect number of arguments\n");
		exit(-1);
	}
	
	int fd;
	struct stat bufferTIME;
	struct stat bufferISREG;
	char *path = argv[0];

	fd = open(path, O_RDONLY);

	if(fd == -1){
		perror("Open");
		exit(-1);
	}

	if(fstat(fd, &bufferTIME) == -1){
		perror("fstat");
		exit(-1);
	}

	if(stat(path, &bufferISREG) == -1){
		perror("stat");
		exit(-1);
	}

	if(S_ISREG(bufferISREG.st_mode)){
		printf("The path corresponds to a regular file\n");
	}
	else{
		printf("The path corresponds to a directory\n");
	}

	printf("Last modification was done %ld seconds after 1 of January 1970\n", bufferTIME.st_mtime);	//I will change it when I know how to do it right
}