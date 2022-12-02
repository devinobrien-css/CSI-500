#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <string.h>
#include <pthread.h>
#include <ctype.h>

/**Structure of thread arguments
*/
struct args {
    char* payload;
    char vowel;
};

/**Writes results to a temporary file
*/
void *writeToFile(void*vargp){
    int fd = open("./bin/temp.inpf",O_CREAT | O_WRONLY);
    if (fd ==-1)
        printf("ERROR: file could not be created");
    write(fd,((struct args*)vargp)->payload,strlen(((struct args*)vargp)->payload));
    close(fd);
    
}

/**Converts specified vowel to uppercase
*/
void *convertVowelToUpper(void*vargp){
    sleep(1);
    char*copy = malloc(sizeof(((struct args*)vargp)->payload));
    sprintf(copy,"%s", ((struct args*)vargp)->payload);
    char vowel = ((struct args*)vargp)->vowel;

    for(int i = 0; i < strlen(((struct args*)vargp)->payload); i++){
        if(copy[i]==vowel) 
            ((struct args*)vargp)->payload[i]=toupper(vowel);
    }
    return NULL;
}

/**Server decorder - splits into several threads to interpret request
*/
int main(){


    struct args *Payload = (struct args*)malloc(sizeof(struct args));
    char payload[] = "Some words here";

    int fd = open("./bin/request.inpf", O_RDONLY);
    if(fd == -1)
        printf("ERROR: file could not be opened");
    char*file_buffer = malloc(1024);
    read(fd,file_buffer,1024);
    close(fd);

    Payload->payload = file_buffer;

	pthread_t thread_id_A;
	pthread_t thread_id_E;
	pthread_t thread_id_I;
	pthread_t thread_id_O;
	pthread_t thread_id_U;
	pthread_t thread_id_digit;
	pthread_t thread_id_writer;

    Payload->vowel = 'a';
	pthread_create(&thread_id_A, NULL, convertVowelToUpper, (void*)Payload);
    pthread_join(thread_id_A, NULL);
    Payload->vowel = 'e';
	pthread_create(&thread_id_E, NULL, convertVowelToUpper, (void*)Payload);
	pthread_join(thread_id_E, NULL);
    Payload->vowel = 'i';
	pthread_create(&thread_id_I, NULL, convertVowelToUpper, (void*)Payload);
	pthread_join(thread_id_I, NULL);
    Payload->vowel = 'o';
	pthread_create(&thread_id_O, NULL, convertVowelToUpper, (void*)Payload);
	pthread_join(thread_id_O, NULL);
    Payload->vowel = 'u';
	pthread_create(&thread_id_U, NULL, convertVowelToUpper, (void*)Payload);
	pthread_join(thread_id_U, NULL);
	pthread_create(&thread_id_writer, NULL, writeToFile, (void*)Payload);
	pthread_join(thread_id_writer, NULL);
	
	exit(0);
}