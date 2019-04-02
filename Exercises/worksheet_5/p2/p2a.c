#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define READ            0
#define WRITE           1


int main(int argc, char* argv[]){

    int parent_fd[2]; 
    int child_fd[2]; 

    pid_t pid;

    if(pipe(parent_fd) == -1)
        exit(-1);

    if(pipe(child_fd) == -1)
        exit(-1);
    
    pid = fork();

    if(pid > 0) {               //parent

        close(parent_fd[READ]);
        close(child_fd[WRITE]);

        int numA, numB;
        scanf("%d%d",&numA,&numB);

        write(parent_fd[WRITE],&numA,sizeof(int));
        write(parent_fd[WRITE],&numB,sizeof(int));

        while(true){

            char currType;
            int nRead = read(child_fd[READ],&currType,sizeof(char));

            if(nRead == 0)
                break;

            if(currType == 'i'){

                int currRes;
                read(child_fd[READ],&currRes,sizeof(int));
                printf("%d \n",currRes);

            }
            else if (currType == 'f'){

                float currRes;
                read(child_fd[READ],&currRes,sizeof(float));
                printf("%f \n",currRes);

            }
            else if (currType == 'E'){

                float currRes;
                read(child_fd[READ],&currRes,sizeof(float));
                printf("INVALIDO \n");
            }

        }

    } else if (pid == 0) {      //child

        close(parent_fd[WRITE]);
        close(child_fd[READ]);

        int numA, numB;
        read(parent_fd[READ],&numA,sizeof(int));
        read(parent_fd[READ],&numB,sizeof(int));

        int sum = numA + numB;
        int sub = numA - numB;
        int mul = numA * numB;
        float div = 0;
        char divR;

        if(numB != 0){
            
            divR = 'f';
            div = (float)numA / numB;
        }
        else{
            divR = 'E';
        }

        write(child_fd[WRITE],"i",sizeof(char));
        write(child_fd[WRITE],&sum,sizeof(int));
        write(child_fd[WRITE],"i",sizeof(char));
        write(child_fd[WRITE],&sub,sizeof(int));
        write(child_fd[WRITE],"i",sizeof(char));
        write(child_fd[WRITE],&mul,sizeof(int));
        write(child_fd[WRITE],&divR,sizeof(char));
        write(child_fd[WRITE],&div,sizeof(float));
        

        //printf(" a + b = %d \n a - b = %d \n a * b = %d \n a / b = %f \n", numA + numB, numA - numB, numA * numB, (float)numA/numB);

        return 0;
    }
    return 0;
}