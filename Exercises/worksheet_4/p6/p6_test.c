#include <stdio.h>
#include <unistd.h>


int main(){


    for(int i = 0; i < 3; i++){

        sleep(5);
        printf("I'm alive! \n");
    }


    printf("Exiting... \n");
    return 0;
}