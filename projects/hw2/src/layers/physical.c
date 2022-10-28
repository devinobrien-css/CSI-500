#include<string.h>
#include<stdio.h>
#include<stdlib.h>

char convert_ASCII_to_char(int ASCII){
    char c = ASCII;
    return c;
}


int convert_char_to_ASCII(char c){
    int ASCII = c;
    return ASCII;
}

void convert_ASCII_to_binary(int ASCII, char**bits){
    int bit_string = 0, index = 1, remainder;

    while(ASCII > 0){
        remainder = ASCII % 2;
        bit_string += (index * remainder);
        ASCII /= 2;
        index *= 10;
    }

    char*prior = malloc(12*sizeof(char));
    sprintf(prior,"%08d",bit_string);
    sprintf(*bits,"%s",prior);
}

int convert_binary_to_ASCII(char* bit_string){
    int bit_value[] = {128,64,32,16,8,4,2,1};
    int bit_index = 0;
    int ASCII_value = 0;
    char c;
    for(int i = 0; i < strlen(bit_string); i++){
        if(bit_index == 7){
            if(bit_string[i] == '0'){
                c = ASCII_value;
            }
            else if(bit_string[i] == '1'){
                ASCII_value += bit_value[bit_index];
                c = ASCII_value;
            }
            bit_index = 0;
            ASCII_value = 0;
        }
        else if(bit_string[i] == '0'){
            bit_index++;
        }
        else if(bit_string[i] == '1'){
            ASCII_value += bit_value[bit_index];
            bit_index++;
        }
    }
    return c;
}

/** Alters bit_string to obide by an odd-parity
 * 
 */
void add_parity(char*bit_string,char**parity_bit_string){
    char temp[9];

    //count number of ones
    int num_ones = 0;
    for(int i = 1; i < strlen(bit_string); i++){
        temp[i-1] = bit_string[i];
        if(bit_string[i]=='1')
            num_ones++;
    }

    //check if parity bit required
    if(num_ones%2 == 0){
        temp[7] = '1';
    }
    else{
        temp[7] = '0';
    }
    temp[8]='\0';
    sprintf(*parity_bit_string,"%s",temp);

}

int check_parity(char*parity_bit_string,char**bit_string){
    char temp[8];
    (*bit_string)[0] = '0';
    //count number of ones
    int num_ones = 0;
    for(int i = 0; i < strlen(parity_bit_string); i++){
        if(i!=0)
            (*bit_string)[i] = parity_bit_string[i-1];
        if(parity_bit_string[i]=='1')
            num_ones++;
    }

    //detected even parity
    if(num_ones%2 == 0){
        printf("--->>>%d",num_ones);
        return -1;
    }
    return 0;
}

int convert_string_to_binary(char*string,char**bit_string){
    if(strlen(string) > 4){
        printf("physical.convert_string_to_binary : given string exceeded maximum buffer size");
        return -1;
    }

    int bit_index = 0;
    char*current_bits = malloc(8*sizeof(char));

    for(int i = 0; i < strlen(string); i++){
        convert_ASCII_to_binary(convert_char_to_ASCII(string[i]),&current_bits);

        for(int j = 0; j < strlen(current_bits); j++){
            (*bit_string)[bit_index] = current_bits[j];
            bit_index+=1;
        }
    }
    (*bit_string)[bit_index] = '\0';
    return 0;
}

int convert_string_to_parity_binary(char*string,char**bit_string){
    if(strlen(string) > 4){
        printf("physical.convert_string_to_binary : given string exceeded maximum buffer size");
        return -1;
    }

    int bit_index = 0;
    char*current_bits = malloc(9*sizeof(char));

    for(int i = 0; i < strlen(string); i++){
        convert_ASCII_to_binary(convert_char_to_ASCII(string[i]),&current_bits);
        
        char*parity_bits = malloc(9*sizeof(char));
        add_parity(current_bits,&parity_bits);
        
        for(int j = 0; j < strlen(parity_bits); j++){
            (*bit_string)[bit_index] = parity_bits[j];
            bit_index+=1;
        }
    }
    (*bit_string)[bit_index] = '\0';
    return 0;
}

int convert_binary_to_string (char*bit_string,char**string){
    int j, i, string_index = 0;
    char*current_bits = malloc(9*sizeof(char));

    for(i = 0; i < strlen(bit_string); i+=8){
        for(j = 0; j < 8; j++){
            current_bits[j] = bit_string[i+j];
        }
        current_bits[j] = '\0';
        (*string)[string_index] = convert_ASCII_to_char(convert_binary_to_ASCII(current_bits));
        string_index+=1;
    }
    (*string)[string_index] = '\0';
    return 0;
}
