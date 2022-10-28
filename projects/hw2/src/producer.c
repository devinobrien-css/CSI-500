#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "encDec.h"

#define READ 0
#define WRITE 1

int main(int argc, char* args[]){
    char*file_buffer = malloc(BUFFER_SIZE*sizeof(char));
    if(read_file("./bin/filename.inpf",&file_buffer) < 0) {
        printf("error reading in file");
        abort();
    }

    int p2c_pipe[2];
    int c2p_pipe[2];

    if(pipe(p2c_pipe) < 0 || pipe(c2p_pipe) < 0){
        printf("pipes could not be created. aborting process.");
        abort();
    }

    pid_t pid = fork();

    if(pid < 0){
        printf("error forking processes. aborting process.\n");
        abort();
    }
    else if(pid == 0){
        /*
            Read encoded frames from pipe, decode, check parity
        */
        close(p2c_pipe[WRITE]);
        int nbytes, payload_size, frame_status = 0, output_index = 0;
        char byte[8];
        char*output = malloc(BUFFER_SIZE*sizeof(char));
        while ((nbytes = read(p2c_pipe[READ], byte, 8)) > 0){
            if(frame_status == 2){
                payload_size = convert_binary_to_ASCII(byte);
                frame_status = 0;
            }
            else if(convert_binary_to_ASCII(byte) == 126){
                frame_status++;
            }
            else{
                char*bit_string = malloc(8*sizeof(char));
                if(check_parity(byte,&bit_string) != 0){
                    printf("parity error reading from pipe. aborting process. %s -> %s",byte,bit_string);
                    abort();
                }
                output[output_index] = toupper(convert_ASCII_to_char(convert_binary_to_ASCII(bit_string)));
                output_index++;
            }
        }
        if (nbytes != 0){
            printf("error reading from pipe");
            exit(2);
        }
        output[output_index]='\0';
        close(p2c_pipe[READ]);

        // write decoded frames to file
        write_file("./bin/filename.outf",output);


        /*
            Encode and write frames to pipe
        */
        close(c2p_pipe[READ]);
        char payload[5];
        int payload_index = 0;
        for(int i = 0; i < strlen(output); i++){
            payload[payload_index] = output[i];
            payload_index++;

            if((i+1)%4 == 0 || i+1 == strlen(output)){
                payload[payload_index] = '\0';
                char*framed_payload = malloc(56*sizeof(char));
                frame(payload,&framed_payload);
                write(c2p_pipe[WRITE], framed_payload, strlen(framed_payload));
                append_file("./bin/filename.chck",framed_payload);
                payload_index = 0;
            }
        }
        close(c2p_pipe[WRITE]);

        exit(0);
    }
    else {
        close(p2c_pipe[READ]);
        char payload[5];
        int payload_index = 0;
        for(int i = 0; i < strlen(file_buffer); i++){
            payload[payload_index] = file_buffer[i];
            payload_index++;

            if((i+1)%4 == 0 || i+1 == strlen(file_buffer)){
                payload[payload_index] = '\0';
                char*framed_payload = malloc(57*sizeof(char));
                frame(payload,&framed_payload);
                write(p2c_pipe[WRITE], framed_payload, strlen(framed_payload));
                append_file("./bin/filename.binf",framed_payload);
                payload_index = 0;
            }
        }
        close(p2c_pipe[WRITE]);
        
        int returnStatus;    
        waitpid(pid, &returnStatus, 0); 
        if(returnStatus != 0){
            printf("child process threw an error. aborting process.\n");
            abort();
        }  

        close(c2p_pipe[WRITE]);
        int nbytes, payload_size, frame_status = 0, output_index = 0;
        char byte[8];
        char*output = malloc(BUFFER_SIZE*sizeof(char));
        while ((nbytes = read(c2p_pipe[READ], byte, 8)) > 0){
            if(frame_status == 2){
                payload_size = convert_binary_to_ASCII(byte);
                frame_status = 0;
            }
            else if(convert_binary_to_ASCII(byte) == 126){
                frame_status++;
            }
            else{
                char*bit_string = malloc(8*sizeof(char));
                check_parity(byte,&bit_string);
                output[output_index] = toupper(convert_ASCII_to_char(convert_binary_to_ASCII(bit_string)));
                output_index++;
            }
        }
        if (nbytes != 0){
            exit(2);
        }
        output[output_index]='\0';
        close(c2p_pipe[READ]);

        write_file("./bin/filename.done",output);
        printf("end of parent: %s", output);
    }
    return 0;
}