#include <stdio.h>

// Print out environment variables

int main(int argc, char* argv[], char* envp[]){

    int i = 0;
    char* currPtr = envp[i];

    while(currPtr != NULL){

        printf("%s \n", currPtr);
        i++;
        currPtr = envp[i];
    }

    return 0;
}
