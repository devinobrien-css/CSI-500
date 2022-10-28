#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <fcntl.h> 
#include <errno.h> 

#define READ 0
#define WRITE 1

#define STDIN 0
#define STDOUT 1

#define BUFFER_SIZE 5000

/** Reads a file into a buffer
 */
int readFile(char* file, char *buffer[BUFFER_SIZE]){
    int fd;
	if((fd = open(file,O_RDONLY)) == -1){
		printf("ERROR\nutility.readFile() : Error accessing file %s \n",*buffer);
        return 1;
	}

    // derive struct of file info
    struct stat file_info;
    int fileInfo = stat(file, &file_info);
    if((fileInfo) != 0){
        printf("ERROR\nutility.readFile() : Error deriving file info from file %s \n",*buffer);
        return 1;
    }

    char buff[file_info.st_size-1];
    read(fd,&buff,file_info.st_size);
    close(fd);
    strcpy(*buffer,buff);
    
    return 0;
}

/** Reads a pipe into a buffer
 */
int readPipe(int pipe[2], char *buffer[BUFFER_SIZE]){
    char ch;
    int index = 0;
    char *buff = (char*)malloc(sizeof(char)*BUFFER_SIZE);
    while(1){
        int value = read(pipe[READ], &ch, sizeof(char));
        if(ch == '\0' || value < 1) break;
        *(buff+index) = ch;
        index++;
    }
    *(buff+index) = '\0';
    strcpy(*buffer,buff);
    return 0;
}

