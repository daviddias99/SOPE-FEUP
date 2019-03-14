#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_CMD_SIZE 50
#define MAX_TOKEN_SIZE 100
#define MAX_TOKEN_NUM 100

int sepTokens(char *command, char **tokenArr)
{

    int tokenCnt = 0;
    tokenArr[tokenCnt] = strtok(command, " ");
    tokenCnt++;

    while (true)
    {
        tokenArr[tokenCnt] = strtok(NULL, " ");

        if (tokenArr[tokenCnt] == NULL)
        {
            break;
        }
        tokenCnt++;
    }

    return tokenCnt;
}

int main(int argc, char *argv[])
{

    int destFD;

    do
    {
        char **tokens = malloc(sizeof(char *) * MAX_TOKEN_NUM);
        char *userCMD = malloc(sizeof(char) * MAX_CMD_SIZE);

        printf("minish >");
        fflush(stdout);
        fgets(userCMD, MAX_CMD_SIZE, stdin);

        int len = strlen(userCMD);
        if (userCMD[len - 1] == '\n')
            userCMD[len - 1] = '\0';

        if (strcmp(userCMD, "quit") == 0)
        {
            free(tokens);
            free(userCMD);
            break;
        }

        if (fork() == 0)
        {

            int nTokens = sepTokens(userCMD, tokens);

            if (nTokens >= 3)
            {
                printf("-o: %s \n",tokens[nTokens - 2]);
                if (strcmp(tokens[nTokens - 2], "-o") == 0)
                {

                    destFD = open(tokens[nTokens - 1], O_WRONLY | O_CREAT, 0644);

                    dup2(destFD, STDOUT_FILENO);

                    tokens[nTokens -2] = NULL;
                }

                
            }
            execvp(tokens[0], tokens);
        }

        wait(NULL);

        free(tokens);
        free(userCMD);
    } while (true);

    return 0;
}