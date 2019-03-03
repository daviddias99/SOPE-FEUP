#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define OF_PERMISSIONS      0644
#define MAX_STRING_SIZE     50


int main(int argc, char* argv[]){

    // print command usage if no arguments were provided
    if(argc == 1){
        printf("Usage: %s <destination> \n",argv[0]);
        return -1;
    }

    // open output file
    int destFD = open(argv[1], O_CREAT | O_WRONLY,OF_PERMISSIONS);

    // check if the file-opening was sucessful
    if(destFD == -1){
        printf("Something went wrong with the output file. \n");
        return -2;
    }

    // variables used to store the current Names and Grades and the number of chars read
    char currentWord[MAX_STRING_SIZE+1];
    currentWord[MAX_STRING_SIZE] = '\0';
    int nChRead,nChWritten;

    do{

        // read the name/grade

        nChRead = read(STDOUT_FILENO,currentWord,MAX_STRING_SIZE);

        if(nChRead == -1){

            printf("Something went wrong. \n");
            return -3;

        }

        // write the name/grade

        nChWritten = write(destFD, currentWord,nChRead);

        if(nChWritten < nChRead){

            printf("Something went wrong. \n");
            return -4;

        }


    }while( (nChRead != 1) && (currentWord[nChRead] != '\n'));

    // close the destination file

    if(close(destFD) == -1){
        printf("Something went wrong with the output file saving. \n");
        return -5;
    }

    return 0;
}