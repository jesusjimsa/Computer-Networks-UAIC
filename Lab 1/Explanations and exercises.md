# Lab 1
## 1. Bash recap. Commands
A shell could be defined as a commands interpreter that provides to the user an interface for the operating system. Bash (Bourne again shell) is one of the most used shells and typically the default one in most of Linux distributions.  
The shell commands can be internal (implemented within the shell) or external (programs running in the console). Any commands can be executed directly by typing it in the shell console. For the external commands the shell will look in the directories specified in the PATH system variable. The contents of the PATH variable can be displayed (as any other variable) using the following console call: echo $PATH. If the PATH variable does not contain the path to the directory where the external command resides, the command can be executed using the complete path starting with the root of the file system /, or a relative path to the current . or parent .. director.  
The typical file system directory in a Linux distribution includes the following:
* / - the root
* bin - various executables used in the system (e.g., the shell, external commands)
* boot - file required in the system booting phase
* dev - files used for interfacing with the physical and logical system peripherical components
* etc - configuration files like /etc/passwd - users information, /etc/group - users groups information, /etc/services - the network services (including the port numbers), /etc/protocols - supported network protocols
* home - users home directories
* lib - shared libraries used by the system or by various applications
* mnt - temporary file systems (mounted using the mount command) for accessing external file systems (e.g., the cdrom or the windows partitions)
* proc - virtual entries corresponding to the processes running in the system and containing information about the used resources (CPU, RAM)
* sbin - executables typically requiring higher privilege (root rights)
* tmp - temporary data
* usr - various applications
* usr/bin - executable files of the applications
* usr/doc - documentation of the applications
* usr/include - header files for usage in C/C++ programs
* usr/lib - libraries required by applications
* usr/local - applications for use on the local machine
* usr/sbin - other executables than included in sbin used for administrative operations on the system
* usr/src - the source files of the applications
* var - variable sized files that are modified frequently (e.g., logs)

To obtain information about a command, its options and parameters, the command can be run using the --help option (typically available). Also, detailed information about the command are provided in the manual, accessible through man the-command or info the-command. 
### 1.1. Commands for operations on the file system
* ls - Lists the files in a directory (default: the current one). Option -l displays the entries in detailed format. Option -a displays the hidden files (name starting with .)
* stat [options] [path] - Displays various informations about the file in the path according to the given options.
* cp [source] [destination] - Copies the source file at the destination. The command can also rename the file when the destination is ending in a file name. The command can be used also to copy folders, using the option -r which recursively copies the included subfolders.
* mv [source] [destination] - Moves the source to the destination. It has the same effect as cp, with the difference that the source is deleted after movement.
* rm [path] - Deletes the file specified in the path. Option -f (force) can be used to bypass a request for additional confirmations. The option -r is required for recursive deletion of directories (including subfolders).
* cd [path] - Changes the current path.
* mkdir [path] - Creates the directory specified in the path.
For more information about the commands please consult the manual. 
### 1.2. Commands for operations with text files
* cat [file] - Displays the entire content of the file.
* less [file] - Displays the content of the file page by page.
* head [file] - Displays the first lines in the file (default 10, the number can be changed with the option -n; e.g.,: -n9 for 9 lines)
* tail [file] - Displays the last lines in the file.
* grep [regular expression] [file] - Searches and displays the lines within the file which comply with the regular expression.
* cut [options] [file] - Extracts certain fields from the file lines based on the selected options.
* diff [file1] [file2] - Compares the files and displays the differences.
* wc [file] - (word count) Displays the number of lines, words and characters in a file.
For more information about the commands please consult the manual.. For editing text files using the console shell various editors can be used: nano, mcedit (simpler) or vim, emacs (more complex). 
### 1.3. Access rights
The access rights on a file can be checked by calling the ls command using option -l. The access rights are displayed in the first field of each entry corresponding to a file. This field contains 10 characters and is formed of four sections. The first section consists in the first character and identifies the type of file ('-' normal file, 'd' directory, 'p' named pipe, etc). The following sections display the access rights on the file. Each section is formed of three characters. The '-' character represents the absence of a right. The 'r' character represents the right to read. The 'w' character represents the right to write. The 'x' character represents the right to execute. Therefore, a section indicating complete rights would be 'rwx'. The first section represents the rights of the file owner. The second section represents the rights of the group. The last section represents the rights of the other users. As an example a set of access rights that permits all operations to the file owner and just reading to the rest of users on a normal file would look like: '-rwxr--r--' . For directories, the execution right refers to the capability to change the current path to the directory and to access its contents, not to list its contents (which corresponds to the right to read). When for a directory, instead of the execution right 'x' is set a 't', this represents that the directory has the 'sticky bit' set. This means that the deletion or the change of files form that directory can be performed only by the directory owners.  
Another value that can be set instead the execution right 'x' is 's'. This indicates (according to the section) that the file has the SUID (Set User ID) bit set or the SGID (Set Group ID) bit set. The setting of this bit means that the file can be executed by anybody with the rights of the owner, or respectively of the group of which the file belongs. The main usage of this bit is to permit other users to execut a command that requires root rights. The change of the access rights can be done by using the following command chmod [users category] [+-=] [rights] [path]. The users category can be 'u' - owner, 'g' - group, 'o' - others or 'a' - all categories. The rights are specified using the characters previously mentioned ('r', 'w', 'x', etc). The chmod command can also be executed using values in base 8 representing the rights in each section. For more information, please consult the manual. 
### 1.4. Redirection of inputs and outputs
The logical devices of input/output are the following: the standard input - stdin, where the input data is read being implicitly associated with the keyboard; the standard output - stdout, where the output data is sent, being implicitly associated with the terminal; the standard error - stderr, where the errors are sent, being also implicitly associated with the terminal.  
The redirection of inputs and outputs can be set using redirection operators. The redirection of the input can be done using the '<' operator. As an example, [program] < [filein], will redirect the input for program from filein. The redirection of the output can be done in a similar manner using the '>' operator. If the '>>' operator is used instead '>' the output data will be appended without overwriting the destination. The rediraction of the standard output can be done using the '2>' operator.  
Redirecting a command as input for another command can be done using the pipe mechanism by chaining the commands using the '|' operator (e.g., ls | less). 

## 2. C programming on Linux. The very basics
The compiler that will be used in Linux during the labs for C sources will be gcc (the C++ sources can be compiled with g++). For the simple compilation of a program without another option an example of the typical call is:  
```
gcc file.c   
```
This will result (when the compilation is error free) in an executable named by default a.out that will be placed in the current directory. To specify a name for the output file the -o option can be used followed by the name. As an example:
```
gcc file.c -o outexe 
```
Implicitly, gcc will search the current directory and the directories containing the headers of the standard libraries in the system for any inclusions that might be necessary. If it is required to include headers placed elsewhere this can be done using option -I followed by the respective path:
```
gcc -I ./custom/include file.c -o outexe 
```
For linking a library the required option is -l followed immediately by the part in the library name that is placed after the lib prefix and before the .a extension (this represents the typical format of library names). For instance the standard library including math functions is named libm.a . For linking this library the gcc call would be:
```
gcc -lm file.c -o outexe 
```
If the library does not reside in the standard locations, to be found by the linker it is needed to specify explicitly its location (including the case of the current directory), by using the -L option, in a similar manner with the -I option used for headers.

## 3. File handling through system calls
A file descriptor in Linux is a simple integer used as index in a file table open by a process. The standard descriptors are:
* 0 - stdin - the standard input
* 1 - stdout - the standard output
* 2 - stderr - the standard error  

The most used I/O calls for accessing and handling files using their descriptors are:

* open() - opens a file  
Required headers and function signatures:
	
```C
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
	
int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);
```

pathname - the path to the file  
flags - options for opening the file (e.g.,: O_RDWR - read and write access)  
mode - specifies explicitly the permissions on the file when creating this (e.g.,: S_IRWXU - the owner user has reading, writing and execution rights)    

The function returns the descriptor associated to the file in case of success and -1 in case of error.

* close() - closing a file 
	Required headers and function signature:  
	```C
	#include <unistd.h>

	int close(int fd);
	```
 
	- fd - the file descriptor (returned by the open call)
	The function returns 0 in case of succes and -1 in case of error.
* read() - reading from a file 
	Required headers and function signature:
	```C
	#include <unistd.h>

	ssize_t read(int fd, void *buf, size_t count);
	```
 
	- fd - the file descriptor (returned by the open call)
	- buf - a pointer to the destination buffer where the read data will be stored
	- count - the number of bytes to be read
	The function returns the number of bytes read in case of success and -1 in case of error.
* write() - writing to a file 
	Required headers and function signature:
	```C
	#include <unistd.h>

	ssize_t write(int fd, void *buf, size_t count);
	```
 
	- fd - the file descriptor (returned by the open call)
	- buf - pointer to the source buffer containing the data to be written in the file
	- count - the number of bytes to be written
	The function returns the number of bytes written in case of success and -1 in case of error.
* fcntl() - File control - execution of various commands on the file 
	Required headers and function signature:
	```C
	#include <unistd.h>
	#include <fcntl.h>

	int fcntl(int fd, int cmd);
	int fcntl(int fd, int cmd, long arg);
	int fcntl(int fd, int cmd, struct flock *lock);
	```
 
	- fd - the file descriptor (returned by the open call)
	- cmd - a constant defining a command to be executed (e.g.,: F_GETFL - obtaining flags describing the file state)
	- arg - an argument specific to the command
	- lock - a structure specific to the lock type commands (e.g.,: for locking the write/read operations)
	The return value depends on the command.
* lseek() - setting the current position in the file   
Required headers and function signature:
	```C
	#include <sys/types.h>
	#include <unistd.h>

	off_t lseek(int fildes, off_t offset, int whence);
	```
 
	- fildes - the file descriptor (returned by the open call)
	- offset - the new position specified in bytes with respect to the reference (negativ - before, positive - after)
	- whence - the reference: SEEK_SET the beginning of the file, SEEK_CUR the current position in the file, SEEK_END the end of the file.  
	The function returns the offset in bytes from the beginning of the file in case of success and -1 in case of error.    

Other calls: 
* fstat() - returns information about the file in a specific structure (stat)
* fchown() - modifies the owner or the group of an open file
* fchmod() - modifies the access rights to a file
* fchdir() - changes the current path

## 4. File handling through library functions
Files can be programmatically used also through a FILE* pointer and the functions included in the stdio library. These permit formatted writing and reading of data.
When a program is using the stdio library, for each of the three open standard streams there exists a FILE* pointer: stdin, stdout and stderr.
The most common operations that can be performed using the stdio library are:
* Opening and closing of files
	
	- FILE *fopen(const char *path, const char *mode); Opens a file. Parameters: path - path to the file, mode - the opening mode (e.g.,: "r+" - read and write) Return: pointer to the open file in case of success and NULL in case of error 
	- int fclose(FILE * stream); Closes a file. Parameters: stream - pointer to the file to be closed Return: 0 in case of success, -1 (EOF - End Of File) in case of error 
* Reading and writing to a file  
	The byte blocks version:
	```C
	size_t fread( void *ptr, size_t size, size_t nmemb, FILE *stream);
	size_t fwrite( const void *ptr, size_t size, size_t nmemb, FILE *stream);
	```
 
	- ptr - pointer to a destination buffer to store the data read or the to the source for the data written
	- size - dimension of a block (record) to be read/written counted in bytes
	- nmemb - the number of blocks (records) to be read/written
	- stream - pointer to the file from which the data is read/in which is written
	- Return: the number of blocks (records) read/written successfully  

The formatted version:
Families of functions using format descriptors for data formatting (e.g.,: "%d" - integer, etc)
Typical signature: function (destination/source, format specifiers, data written/read);  
For writing  
```C
int printf(const char *format, ...);	//writes implicitly to stdout    
int fprintf(FILE *stream, const char *format, ...);	//writes in the stream file     
int sprintf(char *str, const char *format, ...);	//writes in a character buffer pointed by str  
```
 
For reading (similarly with writing)   
```C
int scanf( const char *format, ...);
int fscanf( FILE *stream, const char *format, ...);
int sscanf( const char *str, const char *format, ...);
```
 
Return the number of characters read/written without the implicit end character ('\0') and a negative value in case of error  
Functions that operate at character or line granularity  
The library offers a family of functions for writing/reading a single character or line in the file  
```C
int fgetc(FILE *stream);			//reads one character from stream  
char *fgets(char *s, int size, FILE *stream);	//reads size-1 characters from stream up to maximum the end of the current line  
int getc(FILE *stream);				//similar to fgetc  
int getchar(void);				//reads one caracter from stdin
char *gets(char *s);				//reads one line from stdin 
int fputc(int c, FILE *stream);			//writes one caracter in stream
int fputs(const char *s, FILE *stream);		//writes one line in stream
int putc(int c, FILE *stream);			//similar to fputc
int putchar(int c);				//writes one caracter to stdout 
int puts(const char *s);			//writes one line to stdout 
```
 
* Functions to obtain the state of the file
	```C
	int feof( FILE *stream);
	int ferror( FILE *stream);
	void clearerr( FILE *stream);
	```
 
	- feof - in case of trying to read after reaching the end of the file an internal End Of File will be set and the value returned by this function will be different from 0
	- ferror - returns a value different from 0 if an internal error flag is set (e.g., if we try to write in a file opened only in read mode)
	- clearerr - resets the EOF and error flags
	
* File positioning functions
	```C
	int fseek( FILE *stream, long offset, int whence);
	long ftell( FILE *stream);
	void rewind( FILE *stream);
	```
 
	- fseek - sets the position in the file with respect to the reference; the arguments are similar to lseek
	- ftell - returns the current position in the file
	- rewind - seteaza the position in the file at 0  

Generally, in case of failure of any of the previous functions, the error code will be kept in the global variable errno. For details on the varios error codes please consult the manual entry of the function (man 2 function or man 3 function).

## 5. Directories
The operations on directories are using the structures and functions defined in the dirent.h header. The data structures used in these functions are: DIR - the effective entry on disk for a directory, abstracted as a file stream, and containing a series of other entries (subdirectories and other files) struct dirent - a structure containing information associated to a DIR structure for an entry in the respective directory; includes data like the name in the d_name field as a char array or the type of the entry (file or directory) in the field d_type The functions used for handling directories are the following:
* opendir() - "opens" a directory DIR* opendir(const char* dirname) 
	- dirname - pointer to the directory path
	- return - a pointer to a DIR structure, corresponding to the first entry in the respective directory in case of success and null in case of error
	
* readdir() - reads information about an entry in a directory struct dirent* readdir(DIR* dirp) 
	- dirp - pointer to an entry in the directory
	- return - a pointer to a dirent structure corresponding to the entry indicated by the DIR pointer, followed by advancing to the following entry in the same directory or null in case there is no other entry or in case of error 
	
* rewinddir() - repositions to the first entry in the directory void rewinddir(DIR* dirp) 
	- dirp - pointer to an entry in the directory
	
* telldir() - obtains the index of an entry in the directory off_t telldir(DIR* dirp) 
	- dirp - pointer to an entry in the directory
	- return - an integer representing the current position of the entry in the directory or -1 in case of error
	
* seekdir() - positions to a certain entry in the directory void seekdir(DIR *dir, off_t offset) 
	- dir - pointer to the current entry in the directory
	- offset - the new position which will indicate the current entry
	
* closedir() - "closes" the directory int closedir(DIR* dirp) 
	- dirp - pointer to an entry in the directory
	- return - 0 if the closing was successful or -1 in case of error

## 6. Memory management - quick reminder
We recap in this section the most used memory management functions in C. These require including the header stdlib.h:
* malloc() - allocates a block of memory without initializing it void *malloc(size_t size);
 
	- size - the number of bytes to allocate
	- retur - pointer to the allocated memory, NULL in case of error
	
* calloc() - allocates a block of memory and initializes it with 0 void *calloc(size_t nmemb, size_t size);
 
	- nmemb - the number of blocks to allocate
	- size - the size in bytes to allocate
	- return - pointer to the allocated memory, NULL in case of error
	
* free() - frees a block of memory void free(void *ptr);
 
	- ptr - pointer to a memory location allocated using any of the previous functions

## 7. Exercises
### 7.1. Bash
1. What is the effect of the following command line: ```echo ` who | cut -c1-9 | sort | uniq ` >> users``` ? (hint: use man to find out the effect of the commands). Rename the 'users' file into 'accounts' and copy this into a 'users' subfolder created in the current directory.
2. Display the inode of a file using stat,grep,cut. Can it be done easier? (hint: using just one command)
3. Display all users for who the account name ends in "a".
### 7.2.File handling
1. Given the following file - testpak- write a program that reads from this file a "packet" with the following structure (using I/O system calls) and display the contents of the "fields":
	* source port - integer 0-65535
	* destination port - integer 0-65535
	* length - integer 0-65535
	* checksum - integer 0-65535
	* data - character array of size 32
2. Write a program that implements a recursive find command. 
3. Write a program that receives as input argument a file name or a directory and returns the type of the corresponding disk entry (file or directory) and the time of when the last changes were done (hint: fstat).
