#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 


// Could've used <stdbool.h>
#define true 1
#define false 0

#define MAX_SIZE 200


int main(int argc, char* argv[]){

    if(argc > 1)
        return 1;
    
    char* command = malloc(sizeof(char)*MAX_SIZE);
    char* currentToken = malloc(sizeof(char)*MAX_SIZE);

    char* validOp = fgets(command,MAX_SIZE, stdin);

    if(validOp == NULL)
        return 2;

    currentToken = strtok(command, " ");
    printf("%s ", currentToken);

    while(true){

        currentToken = strtok(NULL, " ");

        if(currentToken == NULL)
            break;

        printf("%s ", currentToken);

    }

    printf("\n");
    return 0;
}