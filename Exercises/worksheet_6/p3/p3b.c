// PROGRAMA p03.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 10

void *PrintHello(void *threadnum)
{
    printf("Hello from thread no. %d!\n", *(int *)threadnum);
    free(threadnum);
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int t;

    for (t = 0; t < NUM_THREADS; t++)
    {
        int* argument = (int*) malloc(sizeof(int));
        *argument = t;

        printf("Creating thread %d\n", *argument);
        pthread_create(&threads[t], NULL, PrintHello, (void *)argument);
    }
    
    pthread_exit(0);
}