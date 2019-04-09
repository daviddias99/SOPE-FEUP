// PROGRAMA p01.c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define STDERR 2


void *thrfunc(void *arg)
{
    pthread_t self_tid = pthread_self();
    
    sleep(1);
    fprintf(stderr, "Thread with TID(%d) and order number(%d) \n", (int) self_tid,*(int*)arg);

    return arg;
}

int main(int argc, char* argv[])
{

    int n = atoi(argv[1]);

    pthread_t* threadArr = (pthread_t*) malloc(n * sizeof(pthread_t));


    for(int i = 0; i < n; i++){

        int* argument = (int*) malloc(sizeof(int));
        *argument = i;

        pthread_create(&threadArr[i],NULL,thrfunc,(void*)argument);

    }

    pthread_exit(NULL);

    //return 0;
}