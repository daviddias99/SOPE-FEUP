
#include <unistd.h> 

int main(){

    int fd[2];

    pipe(fd);

    close(fd[1]);

    int a;

    return  read(fd[0],&a,sizeof(int));;
}