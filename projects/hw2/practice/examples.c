#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h> 

/**
 */
int ASCII_to_binary(int input){
	int result = 0, i = 1, remainder;

    while (input > 0){
            remainder = input % 2;
            result = result + (i * remainder);
            input = input / 2;
            i = i * 10;
    }
    return(result);
}

/**
 */
int char_to_ASCII(char c){
    printf("%c",c);
	int a = c;
    printf("%d",a);
	return a;
}

/**
 */
int convert_to_bitstring(char symbol){
	return ASCII_to_binary(char_to_ASCII(symbol));
}


void convert_to_char(char* bit_string, char output[2]){
    int bit_value[] = {128,64,32,16,8,4,2,1};
    //bit_index is the current bit in a byte
    int bit_index = 0;
    //ASCII_value is a variable to hold the calculated ASCII value of the byte
    int ASCII_value = 0;
    //letter holds the ASCII character of the integer value of the byte

    //LOOP THROUGH ALL BITS IN BINARY FILE | bit_index resets after a byte is read and char value is printed
    for(int i = 0; i < strlen(bit_string); i++)
    {
        if(bit_index == 7)//if the current bit in memory is the eighth bit of a given byte
        {
            if(bit_string[i] == '0')
            {
                sprintf(output,"%c",ASCII_value);
            }
            else if(bit_string[i] == '1')
            {
                ASCII_value += bit_value[bit_index];
                sprintf(output,"%c",ASCII_value);
            }
            bit_index = 0;
            ASCII_value = 0;
        }
        else if(bit_string[i] == '0')
        {
            bit_index++;
        }
        else if(bit_string[i] == '1')
        {
            ASCII_value += bit_value[bit_index];
            bit_index++;
        }
    }
}

void run_test_on_set(char* test_set) {
    printf("running test set");


    for(int i = 0; i < strlen(test_set); i++){
        printf("Current Char: %c\n",test_set[i]);


        char bit_string[9];
        sprintf(bit_string,"0%d",convert_to_bitstring(test_set[i]));

        printf("• binary: %s\n",bit_string);
        printf("• bit length: %lu\n",strlen(bit_string));

        char buff[2];
        convert_to_char(bit_string,buff);
        printf("• convert back: %d\n",buff[0]);
        printf("• convert back: %c\n",buff[0]);

        
        int passed = (buff[0] == test_set[i]);

        if(passed == 1)
            printf("test passed");
        else
            printf("[!!!] test failed");

        printf("\n\n");
    }
}

void test(){
    char* lowercase_set = "abcdefghijklmnopqrstuvwxyz";
    char* uppercase_set = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char* number_set = "0123456789";

    char* symbol_set = "!?+=-:@. $";

    run_test_on_set(lowercase_set);
    run_test_on_set(uppercase_set);
    run_test_on_set(number_set);


}




void files() {
    int fd = open("./bin/input.inpf",O_CREAT | O_WRONLY);

    if (fd ==-1)
        printf("error occurred");

    char* buffer = "Transmit this string";

    int success = write(fd,buffer,strlen(buffer));

    close(fd);
}



/**
 */
int main(){
    printf("EXAMPLES FOR PROJECT TWO\n");
    printf("------------------------------\n");

    printf("testing conversions:\n");

    char bit_string[9];
    sprintf(bit_string,"0%d",convert_to_bitstring('A'));

    printf("convert A to bit string: %s\n",bit_string);
    printf("->length: %lu\n",strlen(bit_string));

    test();

    files();

    printf("%d\n",ASCII_to_binary(22));
    printf("%d\n",ASCII_to_binary(23));


    char letters[] = "abcdefghijklmnopqrstuvwxyz";
    char uppercase[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char numbers[] = "0123456789";
    char symbols[] = "!?+-=%$#&*()[]{}";


    char*c = malloc(8*sizeof(char));
    for(int i = 0; i < strlen(letters); i++){
        convert_ASCII_to_binary(letters[i],&c);
        printf("%s - %lu\n",c,strlen(c));
        printf("%c -> %c\n",letters[i],convert_binary_to_ASCII(c));
    }

    for(int i = 0; i < strlen(uppercase); i++){
        convert_ASCII_to_binary(uppercase[i],&c);
        printf("%s - %lu\n",c,strlen(c));
        printf("%c -> %c\n",uppercase[i],convert_binary_to_ASCII(c));
    }

    for(int i = 0; i < strlen(numbers); i++){
        convert_ASCII_to_binary(numbers[i],&c);
        printf("%s - %lu\n",c,strlen(c));
        printf("%c -> %c\n",numbers[i],convert_binary_to_ASCII(c));
    }

    for(int i = 0; i < strlen(symbols); i++){
        convert_ASCII_to_binary(symbols[i],&c);
        printf("%s - %lu\n",c,strlen(c));
        printf("%c -> %c\n",symbols[i],convert_binary_to_ASCII(c));
    }


    return 1;
}

