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

    char currentWord[MAX_STRING_SIZE+1];
    currentWord[MAX_STRING_SIZE] = '\0';
    int numberRead, numberWritten;

    do{

        numberRead = read(STDOUT_FILENO,currentWord,MAX_STRING_SIZE);

        if(numberRead == -1){

            printf("Something went wrong. \n");
            return -3;

        }

        numberWritten = write(destFD, currentWord,numberRead);

        if(numberWritten < numberRead){

            printf("Something went wrong. \n");
            return -4;

        }


    }while( (numberRead != 1) && (currentWord[numberRead] != '\n'));


    close(destFD);

    return 0;
}