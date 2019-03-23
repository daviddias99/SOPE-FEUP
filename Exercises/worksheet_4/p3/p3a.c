
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>


int delta = 1;


void sigusr_handler(int signo){

    delta = -delta;

}


int main(void) {

    int i;

    struct sigaction usrAction;

    usrAction.sa_handler = sigusr_handler;
    usrAction.sa_flags = 0;
    sigemptyset(&usrAction.sa_mask);

    sigaction(SIGUSR1,&usrAction,NULL );
    sigaction(SIGUSR2,&usrAction,NULL );

    while(true){

        printf("%d \n",i);
        i += delta;

        int numLeft = sleep(1);

        while (numLeft != 0)
            numLeft = sleep(numLeft);
    }


    return 0;
}