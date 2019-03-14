// PROGRAMA p10.c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[], char *envp[])
{
    pid_t pid;
    if ( (argc != 3) && (argc != 2))
    {
        printf("usage: %s dirname [destination]\n", argv[0]);
        exit(1);
    }
    pid = fork();

    if (pid > 0)
        printf("My child is going to execute command\"ls -laR %s\"\n", argv[1]);
    else if (pid == 0)
    {
        if(argc == 3){

            int destFileFD = open(argv[2],O_WRONLY | O_CREAT,0644);
            dup2(destFileFD,STDOUT_FILENO);
        }

        char* arguments[] = {"ls", "-laR", argv[1], NULL};
        execvp("ls", arguments); 

        printf("Command not executed !\n");
        perror("Exec error");
        exit(1);
    }
    exit(0);
}