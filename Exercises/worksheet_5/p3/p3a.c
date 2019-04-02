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

    int fileFD = open(filename,O_RDWR);
    int fd[2];

    pipe(fd);

    int nRead;
    char line[50];

    pid_t PID = fork();

    if(PID == 0){ 

        close(fd[WRITE]);
        dup2(fd[READ],STDIN_FILENO);
        execlp("sort","sort",NULL);
    }
    close(fd[READ]);
    
    while((nRead = read(fileFD,line,50)) != 0 ){

        write(fd[WRITE],line,50);

    }



    return 0;
}