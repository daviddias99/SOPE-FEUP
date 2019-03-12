
#include <sys/types.h>
#include <sys/unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {

    pid_t pid1;

    pid1 = fork();

    if(pid1 > 0){ //parent

        printf("Hello ");
        fflush(stdout);

    }
    else{ //child

        pid_t pid2 = fork();

        if(pid2 > 0) { //parent

            printf("my ");
            fflush(stdout);
        }
        else { //child

            printf("friends!\n");
        }
    }

    return 0;

}





