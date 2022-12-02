/* Client Application
---------------------------
forks to clientEncoder and clientDecoder. sends requests to server
*/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include "encDec.h"

/**Client - sends request to server, awaits response
*/
int main(int argc, char const* argv[]){
	char response_buffer[1024] = {0}; //buffer for recieving response from server
	char request_buffer[1024];

    printf("Enter input to convert:");
    scanf("%[^\n]",request_buffer);

    pid_t pid;
	int fork_status;

    //client socket with TCP bit stream connection
	struct sockaddr_in server_address;
	int client_socket = 0, response_status, client_fd;
	if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
		error("ERROR: client socket could not be created");
    printf("client socket established...\n");

	//encode IPv4/IPv6 addresses 
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	if (inet_pton(AF_INET, LOCALHOST, &server_address.sin_addr) < 1)
		error("ERROR: could not encode client IP");
    printf("client ip encoded...\n");

    //attempt to establish connection to server
	if ((client_fd = connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address))) < 0) 
	    error("ERROR: could not connect to server");
    printf("client connection to server established...\n");


    pid = fork();
    if (pid == -1)
        error("ERROR: server failed to fork");
    else if (pid == 0){ //clientEncoder
        //message server
        send(client_socket, request_buffer, strlen(request_buffer), 0);
        printf("request sent to server...\n");
        exit(0);
    }
    else{//clientDecoder
        if(waitpid(pid, &fork_status, 0) > 0) {
            if(WIFEXITED(fork_status) && !WEXITSTATUS(fork_status)){
                //retrieve response
                response_status = read(client_socket, response_buffer, 1024);
                close(client_fd);
                printf("response received from server...\n");
                printf("response: %s\n", response_buffer);
            }
            else if(WIFEXITED(fork_status) && WEXITSTATUS(fork_status)) {
                if (WEXITSTATUS(fork_status) == 127)
                    error("ERROR: client exec failed\n");
                else
                    error("WARNING: exec returned a non-zero status\n");            
            }
            else
                error("ERROR: client execvp did not terminate successfully");
        }
        else 
            error("ERROR: client parent did not successfully wait for child");
    }
	return 0;
}