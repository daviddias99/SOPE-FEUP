#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define OF_PERMISSIONS      0644
#define MAX_STRING_SIZE     50


struct Student {

    char name[MAX_STRING_SIZE+1];
    int grade;
    
};


int main(int argc, char* argv[]){

    // print command usage if no arguments were provided
    if(argc == 1){
        printf("Usage: %s <source> \n",argv[0]);
        return -1;
    }

    // open input file
    int sourceFD = open(argv[1], O_RDONLY);

    // check if the file-opening was sucessful
    if(sourceFD == -1){
        printf("Something went wrong with the output file. \n");
        return -2;
    }

    // variables for storing the number of bytes read and written
    int nRead,nWritten;

    // variavle used for storing the current Student that is being read
    struct Student currStudent;

    do{

        // read the struct from the file
        nRead = read(sourceFD,&currStudent,sizeof(struct Student));

        if(nRead != sizeof(struct Student))
            break;
   
        if(nRead == -1){

            printf("Something went wrong. \n");
            return -3;

        }


        // read, char by char, the name of the student

        int i = 0;

        while(currStudent.name[i] != '\0'){

            nWritten = write(STDOUT_FILENO,&currStudent.name[i] ,1);
            i++;
        }

        // read the grade of the student

        char gradeStr[5];
        sprintf(gradeStr, "%d", currStudent.grade);

        nWritten = write(STDOUT_FILENO,gradeStr ,2);
        nWritten = write(STDOUT_FILENO,"\n",1);
        nWritten = write(STDOUT_FILENO,"\n",1);

        if(nWritten == -1){

            printf("Something went wrong. \n");
            return -4;

        }


    }while( (nRead == sizeof(struct Student)));

    // close the source file

    if(close(sourceFD) == -1){
        printf("Something went wrong with the input file saving. \n");
        return -5;
    }

    return 0;
}