#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 

#define CHUNK_SIZE 64

int main(int argc, char* argv[]){

    if(argc < 3){

        printf("Invalid number of arguments. \n");
        return -1;
    }


    char chunk[CHUNK_SIZE];

    int sourceFileFD = open(argv[1],O_RDONLY,S_IRUSR | S_IRGRP | S_IROTH);
    int destFileFD= open(argv[1],O_WRONLY,S_IWUSR | S_IWGRP | S_IWOTH);

    ssize_t nRead;

    if((sourceFileFD== -1) || (destFileFD == -1))
        return -2;

    while( (nRead = read(sourceFileFD,chunk,CHUNK_SIZE)) != 0) {
        write(destFileFD,chunk,CHUNK_SIZE);

    close(sourceFileFD);
    close(destFileFD);


    return 0;
}