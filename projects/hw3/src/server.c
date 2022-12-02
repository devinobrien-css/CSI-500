/* Server Application
---------------------------
forks to serverEncoder and serverDecoder. sends responses to clients
*/
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h> 
#include <fcntl.h> 
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h> 
#include <sys/wait.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include "encDec.h"
	
int main(int argc , char *argv[]){
	int server_socket, //a reference to this server's socket
		socket_address_length, //this server's address length
		temp_socket, //temporary socket for new connection from client
		client_socket_set[MAX_CONNECTIONS], //set of connected client sockets
		await_status, //status of server while awaiting requests
		request_status, //status of incoming request
		client_sd; //current client's socket desriptor
	int max_client_sd; //current maximum client socket descriptor
	struct sockaddr_in server_address; //address of server's socket
	fd_set client_fd_set; //client socket file descriptors
	char request_buffer[REQUEST_SIZE]; //this server's request buffer
	char response_buffer[REQUEST_SIZE]; //this server's response buffer

	pid_t pid;
	int fork_status;
		
	//set all potential client sockets to 0
	for (int i = 0; i < MAX_CONNECTIONS; i++){
		client_socket_set[i] = 0;
	}

	//create TCP bit stream server socket
	if((server_socket = socket(AF_INET,SOCK_STREAM,0))==0){
		printf("ERROR: server socket could not be established");
		exit(0);
	}
	printf("server socket established...\n");
	
	//enable server to recieve multiple client connections
	int option=TRUE;
	if(setsockopt(server_socket,SOL_SOCKET,SO_REUSEADDR,(char *)&(option), sizeof(option)) < 0 ){
		printf("ERROR: socket options could not be adjusted");
		exit(0);
	}
	printf("server socket adjusted for multi-connection...\n");

	//define socket metadata
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(PORT);
		
	//bind the socket to localhost port 8888
	if (bind(server_socket,(struct sockaddr*)&server_address, sizeof(server_address))<0){
		printf("Error: server failed to bind to localhost socket #%d",PORT);
		exit(0);
	}
	printf("server listening on port %d...\n", PORT);
		
	//specify max pending connections for server
	if (listen(server_socket, 5) < 0){
		printf("ERROR: could not specify max pending connections");
		exit(0);
	}
	printf("max number of pending connections specified...\n");
		
	socket_address_length = sizeof(server_address);

	//continuously loop and fulfill requests
	while(TRUE){
		FD_ZERO(&client_fd_set); //empty all client socket descriptors
		FD_SET(server_socket, &client_fd_set); //set server socket
		
		//add all potential sockets
		max_client_sd = server_socket;
		for(int i=0; i<MAX_CONNECTIONS; i++){
			client_sd = client_socket_set[i];
			if(client_sd >= 1)
				FD_SET(client_sd, &client_fd_set);
			if(client_sd > max_client_sd)
				max_client_sd = client_sd;
		}
	
		//await request on socket infinitely
		await_status = select(max_client_sd+1, &client_fd_set, NULL, NULL, NULL);
		if ((await_status < 0) && (errno!=EINTR)){
			printf("ERROR: an issue occured waiting for a request");
			exit(0);
		}
			
		//incoming request recieved
		if (FD_ISSET(server_socket, &client_fd_set)){
			if ((temp_socket = accept(server_socket,(struct sockaddr *)&server_address, (socklen_t*)&socket_address_length))<0){
				printf("ERROR: server had trouble accepting request from client");
				exit(0);
			}
			printf("incoming client request:\nSocket FD: %d\nIP: %s\nPort: %d\n", temp_socket, inet_ntoa(server_address.sin_addr), ntohs(server_address.sin_port));
			
			//add new socket to array of sockets
			for (int i = 0; i < MAX_CONNECTIONS; i++){
				//if position is empty
				if( client_socket_set[i] == 0 ){
					client_socket_set[i] = temp_socket;
					printf("added to list of socket connections -> %d...\n" , i);
					break;
				}
			}
		}
			
		for (int i=0; i<MAX_CONNECTIONS; i++){
			client_sd = client_socket_set[i];
				
			if (FD_ISSET(client_sd, &client_fd_set)){
				printf("client interaction detected...\n");
				if ((request_status = read(client_sd, request_buffer, 1024)) == 0){ //request buffer
					//client disconnect
					getpeername(client_sd, (struct sockaddr*)&server_address, (socklen_t*)&socket_address_length);
					printf("client disconnected:\n IP: %s\nPort: %d\n", inet_ntoa(server_address.sin_addr), ntohs(server_address.sin_port));
						
					close(client_sd);
					client_socket_set[i] = 0;
				}
				else{
					request_buffer[request_status] = '\0'; 
					printf("server recieved request: %s\n",request_buffer);
					int fd = open("./bin/request.inpf",O_CREAT | O_WRONLY | O_TRUNC);
					if (fd ==-1)
						printf("ERROR: request file could not be created");
					write(fd,request_buffer,strlen(request_buffer));
					close(fd);

					if((pid = fork()) < -1)
						printf("ERROR: server failed to fork");
					else if(pid == 0){//serverDecoder
						char *args[]={"./serverDecoder", NULL};
						execvp(args[0],args);
						printf("ERROR: execvp failed to run");
						exit(0);
					}
					else{//serverEncoder
						if(waitpid(pid, &fork_status, 0) > 0) {
							if(WIFEXITED(fork_status) && !WEXITSTATUS(fork_status)){

								int fd = open("./bin/temp.inpf", O_RDONLY);
								if(fd == -1)
									printf("ERROR: temp file could not be opened");
								char*file_buffer = malloc(1024);
								read(fd,file_buffer,1024);
								close(fd);
								if(send(client_sd, file_buffer, strlen(file_buffer), 0) != strlen(file_buffer) ){ //request buffer
									printf("ERROR: response could not be sent to client");
								}
								printf("server response sent to client...\n");
							}
							else if(WIFEXITED(fork_status) && WEXITSTATUS(fork_status)) {
								if (WEXITSTATUS(fork_status) == 127)
									printf("ERROR: server exec failed\n");
								else
									printf("WARNING: exec returned a non-zero status\n");            
							}
							else
								printf("ERROR: server execvp did not terminate successfully");
						}
						else 
							printf("ERROR: server parent did not successfully wait for child");
					}
				}
			}
		}
	}
	return 0;
}

