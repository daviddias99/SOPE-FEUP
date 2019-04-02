#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>


// Could've used <stdbool.h>
#define true 1
#define false 0

#define MAX_COMMAND_NUM 10
#define MAX_COMMAND_SIZE 200
#define MAX_TOKEN_SIZE 200
#define MAX_TOKEN_NUM 200

#define READ 0
#define WRITE 1


int main(int argc, char* argv[]){

    if(argc > 1)
        return 1;
    
    // 'tokenCnt' can be ommited as the token array will have a NULL ptr
    // at the last position. I chose to keep it because it might be useful
    // if we need to check the arraysize often.

    int tokenCnt = 0;
    int cmdCnt = 0;

    // string containing the commands obtained from the user
    char* commandsStr = malloc(sizeof(char) * MAX_COMMAND_SIZE);

    // commands holds all the commands given by the user. These commands come from the decomposition of 'commandsStr'
    char** commands = malloc(sizeof(char*) * MAX_COMMAND_NUM);

    // '2d' array that holds all the tokens. This array stores in each 'line' a command given by the user. Each column
    // stores one token from that lines command
    char*** tokens =  malloc(sizeof(char*) * MAX_COMMAND_NUM);

    // memory allocation for the array
    for (int i = 0; i< MAX_COMMAND_NUM; i++) {

         tokens[i] = (char **) malloc(MAX_TOKEN_NUM*sizeof(char **));

          for (int j = 0; j < MAX_TOKEN_NUM; j++) {

              tokens[i][j] = (char *)malloc(MAX_TOKEN_SIZE*sizeof(char *));
          }

    }


    // get the commands from the user
    char* validOp = fgets(commandsStr,MAX_COMMAND_SIZE*MAX_COMMAND_NUM, stdin);

    commandsStr[strlen(commandsStr)-1] = '\0';
    if(validOp == NULL)
        return 2;

    // decompose the given commands

    commands[cmdCnt] = strtok(commandsStr, ";|");
    cmdCnt++;

    while(true){

        commands[cmdCnt] = strtok(NULL, ";|");

        if(commands[cmdCnt] == NULL)
            break;
        
        cmdCnt++;
    }
    
    printf("%d \n",cmdCnt);

    // decompose each command given into tokens
    for (int i = 0; i < cmdCnt; i++)
    {

        commandsStr = commands[i];
        tokenCnt = 0;
        
        tokens[i][tokenCnt] = strtok(commandsStr, " ");
        printf("---- %s \n", tokens[i][tokenCnt]);
        tokenCnt++;
        while (true)
        {

            tokens[i][tokenCnt] = strtok(NULL, " ");
            printf("---- %s \n", tokens[i][tokenCnt]);
            if (tokens[i][tokenCnt] == NULL)
                break;
            tokenCnt++;
        }
    }

    int fd1[2];
    pipe(fd1);


    for(int i = 0; i < cmdCnt; i++){


        pid_t PID1 = fork();

        if(PID1 > 0){

            dup2(fd1[READ],STDIN_FILENO);

            if(i != cmdCnt -1){
                 dup2(fd1[WRITE],STDOUT_FILENO);
            }else{

                close(fd1[WRITE]);
            }

            execvp(tokens[i][0],tokens[i]);

        }

        wait(NULL);
    }

    return 0;
}