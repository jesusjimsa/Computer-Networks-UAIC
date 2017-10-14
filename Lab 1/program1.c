#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
 
int main(int argc, char *argv[]){
	if (argc < 2){
		perror("\nError");
		exit(-1);
	}

	int fd1;
    char buffer[1024], texto[50];
	int numbytes, lectura;
	
	if ((fd1 = open(argv[1],O_RDONLY)) < 0){
        printf("\nError %d en open",errno);
        perror("\nError en open");
        exit(EXIT_FAILURE);
    }

	read(fd1, &lectura, sizeof(int));
	printf("Source port is %d\n", lectura);
	read(fd1, &lectura, sizeof(int));
	printf("Destination port is %d\n", lectura);
	read(fd1, &lectura, sizeof(int));
	printf("Length is %d\n", lectura);
	read(fd1, &lectura, sizeof(int));
	printf("Cheksum is %d\n", lectura);
	read(fd1, &buffer, 32 * sizeof(char));
	printf("Data is %s\n", buffer);
}