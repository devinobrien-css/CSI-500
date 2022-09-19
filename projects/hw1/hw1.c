#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

char* sendString(){
    return "holy shitballs batman";
}

double sendDouble(){
    return 0.9471;
}

int sendInt(){
    return 2;
}


char* forkExample(){
    pid_t pid = fork();

    if(pid == 0){
        return "child\n";
    }
    else if(pid < 0){
        return "error\n";
    }
    else {
        return "parent\n";
    }


}



int main(){
    printf("%s\n",sendString());
    printf("%f\n",sendDouble());
    printf("%d\n",sendInt());
    printf("%s",forkExample());
    return 0;
}