#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h> 
#include <errno.h> 
#include "utility.c"

#define READ 0
#define WRITE 1

#define BUFFER_SIZE 5000

#define STDIN 0
#define STDOUT 1

/** Recieves text data as input, evaluates the
 * number of chars, words and lines. Writes 
 * text and results to output file, then returns 
 * the path to the output file
 */
int main(){
    int char_count = 0;
    int word_count = 0;
    int line_count = 0;
    int word_detected = 0;

    // open output file
    char* path_to_file = "./theCount.txt";
    FILE *output_file = fopen(path_to_file, "w");
    if(output_file == NULL){
        fprintf(stderr,"error opening file\n");
    }

    //read and evaluate input
    int index = 0;
    char * buffer = (char*)malloc(sizeof(char)*BUFFER_SIZE);
    char ch;
    while(1){
        int value = read(STDIN, &ch, sizeof(char));

        // if over reading, break
        if((int)ch < -1)break;

        if(ch == '\0') {
            line_count++;
            if (word_detected) {
                word_detected = 0;
                word_count++;
            }
            break;
        }

        if(ch == ' ' || ch == '\t' || ch == '\0' || ch == '\n') {
            if(ch == ' ')char_count++;
            if (word_detected) {
                word_detected = 0;
                word_count++;
            }
            if(ch == '\0' || ch == '\n') line_count++;
        } 
        else {
            char_count++;
            word_detected = 1;
        }   
        *(buffer+index) = ch;
        index++;
    }
    *(buffer+index) = '\0';

    // print text and results to file
    fprintf(output_file,"%s\n\n",buffer);
    fprintf(output_file,"chars -> %d \nwords -> %d \nlines -> %d\n",char_count,word_count,line_count);

    // write file path back
    printf("%s",path_to_file);
    return 0;
}
