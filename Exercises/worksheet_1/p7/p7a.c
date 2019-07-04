#include <stdlib.h>
#include <stdio.h>

void handler1(void){

    printf("Executing exit handler 1 \n");
    
}

void handler2(void){

    printf("Executing exit handler 2 \n");
    // for b)
    // exit(1);
}

int main(){

    atexit(handler1);    
    atexit(handler2);    
    //atexit(handler1);

    // for b)
    // abort();
    printf("Main done! \n");

    return 0;
}