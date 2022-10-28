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
#include "../encDec.h"

#define READ 0

int read_file(char* file, char *buffer[BUFFER_SIZE]){
    int fd;
	if((fd = open(file,O_RDONLY)) == -1){
		printf("ERROR\napplication.read_file() : Error accessing file %s \n",file);
        return -1;
	}

    // derive struct of file info
    struct stat file_info;
    int fileInfo = stat(file, &file_info);
    if((fileInfo) != 0){
        printf("ERROR\napplication.read_file() : Error deriving file info from file %s \n",file);
        return -1;
    }
    char buff[file_info.st_size-1];
    read(fd,&buff,file_info.st_size);
    close(fd);
    strcpy(*buffer,buff);
    return 0;
}

int write_file(char* file, char*content){
    int fd;
	if((fd = open(file,O_WRONLY | O_CREAT)) == -1){
		printf("ERROR\napplication.write_file() : Error accessing file %s \n",file);
        return -1;
	}
    write(fd,content,strlen(content));
    close(fd);
    return 0;
}

int append_file(char* file, char*content){
    int fd;
	if((fd = open(file,O_WRONLY | O_CREAT | O_APPEND)) == -1){
		printf("ERROR\napplication.write_file() : Error accessing file %s \n",file);
        return -1;
	}
    write(fd,content,strlen(content));
    close(fd);
    return 0;
}

int read_pipe(int pipe[2], char *buffer[BUFFER_SIZE]){
    char ch;
    int index = 0;
    char *buff = (char*)malloc(sizeof(char)*BUFFER_SIZE);
    while(1){
        int value = read(pipe[READ], &ch, sizeof(char));
        if(ch == '\0' || value < 1) break;
        printf("%c",ch);
        *(buff+index) = ch;
        index++;
    }
    *(buff+index) = '\0';
    strcpy(*buffer,buff);
    return 0;
}