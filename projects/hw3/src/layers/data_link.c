#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"../encDec.h"
#include <inttypes.h> // uint32_t, uint8_t
#include <stddef.h>
#include <stdint.h>

/**Frames the given payload
 */
void frame(char*payload,char**frame){    
    char*size = malloc(10*sizeof(char));
    convert_ASCII_to_binary(strlen(payload),&size);
    
    char*encoded_payload = malloc(33*sizeof(char));
    convert_string_to_parity_binary(payload,&encoded_payload);

    sprintf(*frame,"%s%s%s%s",SYN,SYN,size,encoded_payload);
}

/**Deframes the payload from the given frame
 */
void deframe(char*frame,char**payload){
    char size[9];
    char temp[33];
    for(int i = 0; i < strlen(frame); i++){
        printf("%c",frame[i]);
    }
}

