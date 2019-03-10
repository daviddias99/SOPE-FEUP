#include <sys/types.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){

    pid_t pid;
    int argument = atoi(argv[1]);
    pid = fork();


    if(pid == -1){
        perror("fork error");
    }
    if(pid > 0) {

        if(argument == 0)
            printf("world ! \n");
        else
            printf("Hello ");
    }
    else {

        if(argument == 0)
            printf("Hello ");
        else
            printf("world ! \n");
            
    }

    return 0;
}




