#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define OF_PERMISSIONS      0644
#define MAX_STRING_SIZE     50
#define MAX_NUMBER_DIGITS   10


struct Student {

    char name[MAX_STRING_SIZE+1];
    int grade;
    
};


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

    // variables for storing the number of bytes read and written
    int nRead;

    // read pairs of students and grades
    do{

        struct Student currStudent;

        // read the student name

        nRead = read(STDOUT_FILENO, currStudent.name, MAX_STRING_SIZE);
        currStudent.name[nRead] = '\0';

        // check if only 'Enter' was pressed
        if(nRead == 1)
            break;

        // read the grade of the student

        char grade[MAX_NUMBER_DIGITS+1];
        nRead = read(STDOUT_FILENO, grade, MAX_NUMBER_DIGITS);
        grade[nRead] = '\0';
        currStudent.grade = atoi(grade);


        if(nRead == -1){

            printf("Something went wrong. \n");
            return -3;

        }

        // write the struct in the destination file
        write(destFD, &currStudent,sizeof(struct Student));


    }while(nRead != 1);


    // close the destination file

    if(close(destFD) == -1){
        printf("Something went wrong with the output file saving. \n");
        return -5;
    }

    return 0;
}