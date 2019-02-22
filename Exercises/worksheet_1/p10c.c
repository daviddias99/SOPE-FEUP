#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 


// Could've used <stdbool.h>
#define true 1
#define false 0

#define MAX_COMMAND_NUM 10
#define MAX_COMMAND_SIZE 200
#define MAX_TOKEN_SIZE 200
#define MAX_TOKEN_NUM 200


int main(int argc, char* argv[]){

    if(argc > 1)
        return 1;
    
    // 'tokenCnt' can be ommited as the token array will have a NULL ptr
    // at the last position. I chose to keep it because it might be useful
    // if we need to check the arraysize often.

    int tokenCnt = 0;
    int cmdCnt = 0;

    char** commands = malloc(sizeof(char*) * MAX_COMMAND_NUM);
    char*** tokens =  malloc(sizeof(char*) * MAX_TOKEN_NUM*MAX_TOKEN_SIZE*MAX_COMMAND_NUM);
    char* commandsStr = malloc(sizeof(char) * MAX_COMMAND_SIZE);

    char* validOp = fgets(commandsStr,MAX_COMMAND_SIZE*MAX_COMMAND_NUM, stdin);

    if(validOp == NULL)
        return 2;

    commands[cmdCnt] = strtok(commandsStr, ";");
    commands[cmdCnt] = strtok(commandsStr, "|");
    cmdCnt++;

    while(true){

        commands[cmdCnt] = strtok(NULL, ";");

        if(commands[cmdCnt] == NULL)
            break;
        cmdCnt++;
    }

    for (int i = 0; i < cmdCnt; i++)
    {

        commandsStr = commands[i];

        if (validOp == NULL)
            return 2;
        tokenCnt = 0;
        tokens[cmdCnt][tokenCnt] = strtok(commandsStr, " ");
        tokenCnt++;

        while (true)
        {

            tokens[cmdCnt][tokenCnt] = strtok(NULL, " ");

            if (tokens[cmdCnt][tokenCnt] == NULL)
                break;
            tokenCnt++;
        }
    }

    for(int i = 0; i < cmdCnt; i++){
        
        int j = 0;
        do{

            char* currToken = tokens[cmdCnt][j];
            
            if(currToken == NULL)
                break;
            
            printf("%s ", currToken);

        }while(1);
        printf("\n");
    }

    return 0;
}