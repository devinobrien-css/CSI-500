#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>


char* sendString(){
    return "sending a string";
}
double sendDouble(){
    return 0.9471;
}
int sendInt(){
    return 2;
}

int deriveStringAddress(char* data){
 return *data;
}

/** Example of a forking process where parent waits
 */
char* forkParentWaitExample(){
    pid_t pid = fork();

    if(pid == 0){
        return "child\n";
    }
    else if(pid < 0){
        return "error\n";
    }
    else {
        return "parent\n";
    }
}



/** Example of a forking process
 */
char* forkExample(){
    pid_t pid = fork();

    if(pid == 0){
        char *args[]={"./executor",NULL};
        execvp(args[0],args);

        printf("error in child pgm\n");
        exit(0); 
    }
    else if(pid < 0){
        return "error\n";
    }
    else {
        int returnStatus;    
        waitpid(pid, &returnStatus, 0);  // parent process waits for child
        printf("parent\n");
        // verify child terminated 
        if(returnStatus == 0){
            return "The child process terminated normally.\n";
        }
        else {
            return "The child process terminated with an error!.\n";
        }
    }
}


#define MSGSIZE 16
char* msg1 = "hello, world\n";

int pipeExample(){
    char buffer[MSGSIZE];
    int p[2];

    if(pipe(p) < 0)
        exit(1);

    write(p[1], msg1, MSGSIZE);
    read(p[0], buffer, MSGSIZE);
    printf("returned from pipe: %s", buffer);
    return 0;   
}

#define BUFFER_SIZE 16
char* resp = "response";

int forkToPipe(){
    char buffer[BUFFER_SIZE];
    int nbytes;
    int p[2];
    pipe(p); 

    pid_t pid = fork();
  
    // pipe failed
    if (p < 0)
        exit(1);
    
    if(pid == 0){
        dup2(p[1],1);
        printf("child executing\n");

        wait(NULL);
        printf("im okay");
        char *args[]={"./executor",NULL};
        execvp(args[0],args);

        printf("error in child pgm\n");
        return 0;
    }
    else if(pid < 0){
        printf("error\n");
    }
    else{
        
        printf("parent\n");
        int returnStatus;    
        waitpid(pid, &returnStatus, 0);  // parent process waits for child
        printf("i waited!\n");

        // verify child terminated 
        if(returnStatus == 0)
            printf("The child process terminated normally. Response:\n");
        else 
            printf("The child process terminated with an error!.\n");

        while (1) {
            char temp;
            if (read(p[0], &temp, 1) < 1) return 0;
            printf("%c", temp);
        }

        printf("\nfinal");
        return 0;
    }
    return 0;
}



/** Executor for homework 1
 */
int main(){
    // printf("%s\n",sendString());
    // printf("%f\n",sendDouble());
    // printf("%d\n",sendInt());

    // pipeExample();

    // char* testAddr = "testAddress";
    // printf("address of %s is %d\n",testAddr,deriveStringAddress(testAddr));


    // printf("%s",forkExample());

    forkToPipe();
    return 0;
}