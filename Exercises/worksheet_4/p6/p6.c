#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>

pid_t childPid;
int reason;


void alarm_handler(int signo){

    kill(childPid,SIGKILL);
    reason = 1;
}


void chld_hanlder(int signo) {

    wait(NULL);
    reason = 0;
}

int main(int argc, char* argv[]){


    if(argc < 3){

        printf("Usage: %s <seconds> <program> [args] \n",argv[0]);
        return -1;
    }

    struct sigaction sigact;

    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = 0;
    sigact.sa_handler = alarm_handler;

    sigaction(SIGALRM,&sigact,NULL);

    sigact.sa_handler = chld_hanlder;
    sigaction(SIGCHLD,&sigact,NULL);


    int t = atoi(argv[1]);

    if((childPid = fork()) == 0){

        execvp(argv[2],&argv[2]);
    }else
        alarm(t);
    
    pause();

    if(reason != 0)
        printf("forced\n");
    else
        printf("died\n");
    

    return 0;
}