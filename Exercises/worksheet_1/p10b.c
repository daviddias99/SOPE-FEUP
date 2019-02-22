#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 


// Could've used <stdbool.h>
#define true 1
#define false 0

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

    char** tokens =  malloc(sizeof(char*) * MAX_TOKEN_NUM);
    char* command = malloc(sizeof(char) * MAX_COMMAND_SIZE);

    char* validOp = fgets(command,MAX_COMMAND_SIZE, stdin);

    if(validOp == NULL)
        return 2;

    tokens[tokenCnt] = strtok(command, " ");;
    tokenCnt++;

    while(true){

        tokens[tokenCnt] = strtok(NULL, " ");

        if(tokens[tokenCnt] == NULL)
            break;
        tokenCnt++;
    }

    for(int i = 0; i < tokenCnt; i++)
        printf("%s ", tokens[i]);
    
    printf("\n");

    return 0;
}