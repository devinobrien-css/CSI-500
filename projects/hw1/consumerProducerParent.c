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
#include "utility.c"

#define READ 0
#define WRITE 1

#define STDIN 0
#define STDOUT 1

#define BUFFER_SIZE 5000


/** Forks to a child and parent process 
 * with full duplex communication 
 * established
 */
int main( int argc, char *argv[] ){
    // initialize pipes
	int pipe1[2];
	int pipe2[2];
	pid_t pid;
	if (pipe(pipe1) == -1) {
		printf("failed to create pipe 1\n");
		return 1;
	}
	if (pipe(pipe2) == -1) {
		printf("failed to create pipe 2\n");
		return 1;
	}

    // fork processes
	pid = fork();
	if (pid < 0) { 
        printf("failed to fork\n");
		return 1;
	}
	else if (pid > 0) {  
        // print metadata
        printf("PARENT PROCESS:\n");
        printf("----------------------------------\n");
        printf("pid: %d\n",pid);
        printf("----------------------------------\n\n");

        // read in content from file
        char *file_buffer = (char*)malloc(sizeof(char)*BUFFER_SIZE);
        readFile(argv[1], &file_buffer);

        // write file content to pipe
        close(pipe1[READ]);
        write(pipe1[WRITE], file_buffer, strlen(file_buffer)+1);
		close(pipe1[WRITE]);

        // wait for child to execute
		int returnStatus;    
        waitpid(pid, &returnStatus, 0);  
        if(returnStatus != 0){
            printf("ERROR \n main.main() The child process terminated with an error.\n");
            return 1;
        }

        // read from pipe
        close(pipe2[WRITE]);
        char * pipe_buffer = (char*)malloc(sizeof(char)*BUFFER_SIZE);
        readPipe(pipe2,&pipe_buffer);
        close(pipe2[READ]);

        // read in from file
        char * final_input_buffer = (char*)malloc(sizeof(char)*BUFFER_SIZE);;
        readFile(pipe_buffer, &final_input_buffer);

        // print metadata
        printf("RESULTS:\n");
        printf("----------------------------------\n");
        printf("%s",final_input_buffer);
        printf("----------------------------------\n\n");
	}
	else { 
        // print metadata
        printf("CHILD PROCESS:\n");
        printf("----------------------------------\n");
        printf("pid: %d\n",pid);
        printf("----------------------------------\n\n");

        // route std i/o of process
        close(pipe1[WRITE]);
        close(pipe2[READ]);
		dup2(pipe1[READ],STDIN);
        dup2(pipe2[WRITE],STDOUT);

        // execute child program
        char *args[]={"./producerConsumerChild",NULL};
        execvp(args[0],args);
        printf("execvp failed\n");
		exit(0);
	}
    return 0;
}
