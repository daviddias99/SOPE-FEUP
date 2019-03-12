// PROGRAMA p8.c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(int argc, char *argv[], char *envp[])
{
    pid_t pid;
    if (argc != 2)
    {
        printf("usage: %s dirname\n", argv[0]);
        exit(1);
    }
    pid = fork();
    if (pid > 0){

        printf("My child is going to execute command\"ls -laR %s\"\n", argv[1]);

        int childStatus;
        wait(&childStatus);
        printf("My son finished executing and returned %d.\n",childStatus);

        if (WIFEXITED(childStatus))
            printf("normal termination, exit status = %d\n", WEXITSTATUS(childStatus));
        else if (WIFSIGNALED(childStatus))
            printf("abnormal termination \n");

    }
        

    else if (pid == 0)
    {
        // execlp("ls", "ls", "-laR", argv[1],NULL);    //     8a
        // execl("/bin/ls", "ls","-laR", argv[1],NULL); //     8b

        /*
        char* arguments[] = {"ls", "-laR", argv[1], NULL};
        execvp("ls", arguments); *///                          8c

        /*
        char* arguments[] = {"ls", "-laR", argv[1], NULL};
        execv("/bin/ls", arguments);  *///                    8d

        char* arguments[] = {"ls", "-laR", argv[1], NULL};

        execve("/bin/ls", arguments, envp); 

        printf("Command not executed !\n");
        exit(1);
    }
    exit(0);
}