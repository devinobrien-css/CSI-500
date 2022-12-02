#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <errno.h> 
#include"../encDec.h"

void error(char*message){
    perror(message);
    exit(0);
}