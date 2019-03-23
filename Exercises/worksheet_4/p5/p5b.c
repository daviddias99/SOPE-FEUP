// PROGRAMA p05a.c
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>

void sig_chld_handler(int signo){


    wait(NULL);

}


int main(void)
{
    pid_t pid;
    int i, n;

    struct sigaction usrAction;

    usrAction.sa_handler = SIG_IGN;
    usrAction.sa_flags = 0;
    sigemptyset(&usrAction.sa_mask);

    sigaction(SIGCHLD,&usrAction,NULL);


    for (i = 1; i <= 20; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            printf("CHILD no. %d (PID=%d) working ... \n", i, getpid());
            sleep(15); // child working ...
            printf("CHILD no. %d (PID=%d) exiting ... \n", i, getpid());
            exit(0);
        }
    }
    for (i = 1; i <= 4; i++)
    {
        printf("PARENT: working hard (task no. %d) ...\n", i);
        n = 20;
        while ((n = sleep(n)) != 0);
        printf("PARENT: end of task no. %d\n", i);

    }
    exit(0);
}