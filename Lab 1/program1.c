#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
 
int main(int argc, char *argv[]){
	if (argc < 2){
		perror("\nError");
		exit(-1);
	}

	int fd1;
    char buffer[1024], texto[50];
	int numbytes;
	
	if ((fd1 = open(argv[1],O_RDONLY)) < 0){
        printf("\nError %d en open",errno);
        perror("\nError en open");
        exit(EXIT_FAILURE);
    }

	read(fd, &buffer, sizeof(int);
	printf("Source port is %i", buffer);
	read(fd, &buffer, sizeof(int);
	printf("Destination port is %i", buffer);
	read(fd, &buffer, sizeof(int);
	printf("Length is %i", buffer);
	read(fd, &buffer, sizeof(int);
	printf("Cheksum is %i", buffer);
	read(fd, &buffer, sizeof(int);
	printf("Cheksum is %i", buffer);



}