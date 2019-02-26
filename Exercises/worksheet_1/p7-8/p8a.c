#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <unistd.h>
#include <inttypes.h>


int main(int argc, char* argv[]){

    srand(time(NULL));

    struct tms tmsInit;
    struct tms tmsFinal;
    long ticks = sysconf(_SC_CLK_TCK);

    clock_t start = times(&tmsInit);

    if(argc != 3)
        exit(1);

    int n1 = atoi(argv[1]);
    int n2 = atoi(argv[2]);

    int currNum;
    int iterCnt = 0;

    do{

        currNum = rand() % n1;
        printf("%d - %d\n", iterCnt,currNum);
        iterCnt++;

    }while(currNum != n2);
    
    clock_t end = times(&tmsFinal);

    /*
    clock_t sysTimeTicks = tmsFinal.tms_stime - tmsInit.tms_stime ;
    printf("System ticks/seconds: %f | %f \n",(float)final,(float)sysTimeTicks/ sysconf(_SC_CLK_TCK));
    clock_t usrTimeTicks = tmsFinal.tms_utime - tmsInit.tms_utime ;
    printf("User ticks/seconds: %f | %f \n",(float)usrTimeTicks,(float)usrTimeTicks/ sysconf(_SC_CLK_TCK));
    */

    printf("Clock: %4.2f s\n", (double)(end - start) / ticks);
    printf("User time: %4.2f s\n", (double)tmsFinal.tms_utime / ticks);
    printf("System time: %4.2f s\n", (double)tmsFinal.tms_stime / ticks);
    printf("Children user time: %4.2f s\n", (double)tmsFinal.tms_cutime / ticks);
    printf("Children system time: %4.2f s\n", (double)tmsFinal.tms_cstime / ticks);
}
