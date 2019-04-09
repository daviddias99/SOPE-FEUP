// PROGRAMA p01.c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define STDERR 2
#define NUMITER 10000

void *thrfunc1(void *arg)
{
    int i;
    fprintf(stderr, "Starting thread %c\n", *(char *)arg);

    for (i = 1; i <= NUMITER; i++)
        write(STDERR, arg, 1);

    return NULL;
}

void *thrfunc2(void *arg)
{
    int i;
    fprintf(stderr, "Starting thread %d\n", *(int *)arg);
    char temp[6];

    sprintf(temp,"%d",*(int*)arg);

    for (i = 1; i <= NUMITER; i++)
        write(STDERR,temp, strlen(temp));

    return NULL;
}


int main(int argc, char* argv[])
{
    pthread_t ta, tb;

    char parameter1 = 'a';
    int  parameter2 = 2;


    pthread_create(&ta, NULL, thrfunc1, &parameter1);
    pthread_create(&tb, NULL, thrfunc2, &parameter2);
    pthread_join(ta, NULL);
    pthread_join(tb, NULL);
    return 0;
}