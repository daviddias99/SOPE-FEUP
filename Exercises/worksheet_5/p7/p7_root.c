
#include <wait.h>
#include <stdlib.h>

int main(){

        
    mkfifo("/tmp/fifo_req", 0660);
    mkfifo("/tmp/fifo_ans", 0660);

    if(fork() > 0){

        execlp("p7_server","p7_server",NULL);

    }else{


        execlp("p7_user", "p7_user",NULL);
    }



    return 0;
}   