#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h> 

#define CHUNK_SIZE 64

int main(int argc, char* argv[]){

    if(argc < 2){

        printf("Invalid number of arguments. \n");
        return -1;
    }

    char chunk[CHUNK_SIZE];
    ssize_t nRead;

    int sourceFileFD = open(argv[1],O_RDONLY);
    int destFileFD= open(argv[2],O_WRONLY | O_CREAT | O_EXCL,0644);

    if(argc == 3)
        dup2(destFileFD,STDOUT_FILENO);

    if((sourceFileFD== -1))
        return -2;

    while( (nRead = read(sourceFileFD,chunk,CHUNK_SIZE)) != 0) 
        write(STDOUT_FILENO,chunk,nRead);

    printf("\n");
    close(sourceFileFD);
    close(destFileFD);

    return 0;
}