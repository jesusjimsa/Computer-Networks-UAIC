/*
	Given the following file - testpak- write a program that reads
	from this file a "packet" with the following structure (using
	I/O system calls) and display the contents of the "fields":
		• source port - integer 0-65535
		• destination port - integer 0-65535
		• length - integer 0-65535
		• checksum - integer 0-65535
		• data - character array of size 32
*/

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

	int fd;
    char buffer[1024], texto[50];
	int numbytes, lectura;
	
	if ((fd = open(argv[1],O_RDONLY)) < 0){
        printf("\nError %d en open",errno);
        perror("\nError en open");
        exit(EXIT_FAILURE);
    }

	read(fd, &lectura, sizeof(int));
	printf("Source port is %d\n", lectura);
	read(fd, &lectura, sizeof(int));
	printf("Destination port is %d\n", lectura);
	read(fd, &lectura, sizeof(int));
	printf("Length is %d\n", lectura);
	read(fd, &lectura, sizeof(int));
	printf("Cheksum is %d\n", lectura);
	read(fd, &buffer, 32 * sizeof(char));
	printf("Data is %s\n", buffer);
}