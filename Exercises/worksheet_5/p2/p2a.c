#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>

#define READ            0
#define WRITE           1

struct operands {

    int a;
    int b;
};


int main(int argc, char* argv[]){

    int fd[2]; 
    pid_t pid;
    struct operands ops;

    if(pipe(fd) == -1)
        exit(-1);
    
    pid = fork();

    if(pid > 0) {               //parent

        close(fd[READ]);
        scanf("%d%d",&ops.a,&ops.b);
        write(fd[WRITE],&ops,sizeof(struct operands));

    } else if (pid == 0) {      //child

        close(fd[WRITE]);
        read(fd[READ],&ops,sizeof(struct operands));

        if(!ops.b)  return 1;
            
        printf(" a + b = %d \n a - b = %d \n a * b = %d \n a / b = %f \n", ops.a + ops.b, ops.a - ops.b, ops.a * ops.b, (float)ops.a/ops.b);

        return 0;
    }
    
    return 0;
}