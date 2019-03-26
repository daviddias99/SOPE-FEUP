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
        int numA, numB;
        scanf("%d%d",&numA,&numB);
        write(fd[WRITE],&numA,sizeof(int));
        write(fd[WRITE],&numB,sizeof(int));

    } else if (pid == 0) {      //child

        int numA, numB;
        read(fd[READ],&numA,sizeof(int));
        read(fd[READ],&numB,sizeof(int));

        if(numB == 0)
            return 1;

        printf(" a + b = %d \n a - b = %d \n a * b = %d \n a / b = %f \n", numA + numB, numA - numB, numA * numB, (float)numA/numB);

        return 0;
    }




    return 0;
}




