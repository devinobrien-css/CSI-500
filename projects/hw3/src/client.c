// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#define PORT 8888
#define LOCALHOST "127.0.0.1"

int main(int argc, char const* argv[]){

	char response_buffer[1024] = { 0 }; //buffer for recieving response from server
	char* request_buffer = "Convert this statement serverside."; //buffer for holding request to server



    //build client socket with TCP connection
	struct sockaddr_in server_address;
	int client_socket = 0, response_status, client_fd;
	if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("ERROR: client socket could not be created");
        exit(0);
	}
    printf("client socket established...\n");

	//encode IPv4/IPv6 addresses 
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	if (inet_pton(AF_INET, LOCALHOST, &server_address.sin_addr) < 1) {
		printf("ERROR: could not encode client IP");
        exit(0);
	}
    printf("client ip encoded...\n");

    //attempt to establish connection to server
	if ((client_fd = connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address))) < 0) {
		printf("ERROR: could not connect to server");
		return -1;
	}
    printf("client connection to server established...\n");

    //message server
	send(client_socket, request_buffer, strlen(request_buffer), 0);
	printf("request sent to server...\n");

    //retrieve response
	response_status = read(client_socket, response_buffer, 1024);
	close(client_fd);
    printf("response received from server...\n");
	printf("%s\n", response_buffer);

	return 0;
}