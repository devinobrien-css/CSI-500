#ifndef ENCDEC_H_
#define ENCDEC_H_
#define BUFFER_SIZE 10000
#define FRAME_BUFFER_SIZE 56
#define SYN "01111110"
#define PORT 8888
#define LOCALHOST "127.0.0.1"
#define TRUE 1
#define FALSE 0
#define MAX_CONNECTIONS 10
#define REQUEST_SIZE 1025 

void error(char*message);

void frame(char*payload,char**frame);

void deframe(char*frame,char**payload);

char convert_ASCII_to_char(int ASCII);

int convert_char_to_ASCII(char c);

int convert_ASCII_to_binary(int ASCII,char**bit_string);

int convert_binary_to_ASCII(char*bit_string);

int convert_string_to_parity_binary(char*string,char**bit_string);

int convert_string_to_binary(char*string,char**bit_string);

int convert_binary_to_string (char*bit_string,char**string);

int read_file(char* file, char *buffer[BUFFER_SIZE]);

int write_file(char* file, char*content);

int append_file(char* file, char*content);

int read_pipe(int pipe[2], char *buffer[BUFFER_SIZE]);

void add_parity(char*bit_string,char**string);

int check_parity(char*bit_string,char**string);

#endif