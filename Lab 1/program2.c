/*
	Write a program that implements a recursive find command.
*/

#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	if (argc < 2){
		perror("\nError");
		exit(-1);
	}

	DIR dirp;
	struct dirent direc;
	char *buscando = argv[1];

	dirp = opendir(".");
	direc = readdir(dirp);

	while(buscando != direc.d_name){
		direc = readdir(dirp);
	}
}