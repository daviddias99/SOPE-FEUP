// PROGRAMA p02.c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define STDERR 2
#define TOTALCHRS 50000

int charCnt = TOTALCHRS;

void *thrfunc(void *arg)
{
    int* nWritten = (int*)malloc(sizeof(int));
    *nWritten = 0;

    fprintf(stderr, "Starting thread %s\n", (char *)arg);

    while(charCnt > 0){

        write(STDERR, arg, 1);
        charCnt--;
        (*nWritten)++;
    }
        

    return nWritten;
}

int main()
{
    pthread_t ta, tb;
    void* nW1;
    void* nW2;

    pthread_create(&ta, NULL, thrfunc, "1");
    pthread_create(&tb, NULL, thrfunc, "2");
    pthread_join(ta, &nW1);
    pthread_join(tb, &nW2);

    printf("\nThread A: %d\nThread B: %d \n",*(int*)nW1,*(int*)nW2);

    free(nW1);
    free(nW2);

    return 0;
}