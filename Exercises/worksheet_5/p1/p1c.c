#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>

#define READ            0
#define WRITE           1


int main(int argc, char* argv[]){

    int fd[2]; 
    pid_t pid;

    if(pipe(fd) == -1)
        exit(-1);
    
    pid = fork();

    if(pid > 0) {               //parent

        close(fd[READ]);
        char line[30];
        memset(line,0,30);

        read(STDIN_FILENO,line,30);
        write(fd[WRITE],line,strlen(line));


    } else if (pid == 0) {      //child

        char line[30];
        while( read(fd[READ],line,30) <= 0);
        int numA, numB;

        sscanf(line,"%d%d",&numA,&numB);

        if(!numB) return 1;
            
        printf(" a + b = %d \n a - b = %d \n a * b = %d \n a / b = %f \n", numA + numB, numA - numB, numA * numB, (float)numA/numB);

        return 0;
    }




    return 0;
}



