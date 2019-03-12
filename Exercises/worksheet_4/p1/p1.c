// PROGRAMA p01a.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#define _XOPEN_SOURCE

void sigint_handler(int signo)
{
    printf("In SIGINT handler ...\n");
}
int main(void)
{
    /*
    struct sigaction act;

    sigemptyset(&act.sa_mask);

    act.sa_handler = sigint_handler;
    act.sa_flags = 0; 

    if (sigaction(SIGINT, &act, NULL) < 0) */
    
    if (signal(SIGINT, sigint_handler) < 0)
    {
        fprintf(stderr, "Unable to install SIGINT handler\n");
        exit(1);
    }
    printf("Sleeping for 30 seconds ...\n");
    int numLeft = sleep(30);

    // 1b
    while(numLeft != 0)
        numLeft = sleep(numLeft);

    printf("Waking up ...\n");
    exit(0);
}