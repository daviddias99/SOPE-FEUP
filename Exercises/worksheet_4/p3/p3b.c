
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>


int delta = 1;


void sigusr_handler(int signo){

    delta = -delta;
}

int randomBetween(int a, int b){

    return (rand() % (b-a)) + a;

}


int main(void) {

    srand(time(NULL));
    int i;
    struct sigaction usrAction;

    usrAction.sa_handler = sigusr_handler;
    usrAction.sa_flags = 0;
    sigemptyset(&usrAction.sa_mask);

    pid_t pid= fork();

    if(pid > 0) { //parent

        //  NOTA: pode acontecer que o processo envie o primeiro sigusr1 antes que o filho instale o handler
        //  usar sigsuspend para evitar isso.

        usrAction.sa_handler = SIG_IGN;
        sigaction(SIGUSR1, &usrAction, NULL);
        sigaction(SIGUSR2, &usrAction, NULL);

        do{

            if(randomBetween(1,4) == 2)
                kill(pid,SIGUSR1);
            
            sleep(1);

        }while( waitpid((pid_t)0,NULL,WNOHANG) == 0);

        
    }else { //child

        sigaction(SIGUSR1, &usrAction, NULL);
        sigaction(SIGUSR2, &usrAction, NULL);


        for(int j = 0; j < 50; i+=delta,j++){

            printf("%d \n", i);

            int numLeft = sleep(1);

            while (numLeft != 0)
                numLeft = sleep(numLeft);  
        }
    } 

    return 0;
}