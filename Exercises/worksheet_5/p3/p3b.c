#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define READ            0
#define WRITE           1


int main(int argc, char* argv[]){

    if(argc != 2)
        return -1;

    char* filename = argv[1];

    int fd[2];

    pipe(fd);

    pid_t PID = fork();

    if(PID == 0){ 
        
        close(fd[WRITE]);
        dup2(fd[READ],STDIN_FILENO);
        execlp("sort","sort",NULL);
    }
    else{

        close(fd[READ]);
        dup2(fd[WRITE],STDOUT_FILENO);
        execlp("cat","cat",filename,NULL);

    }

    return 0;
}