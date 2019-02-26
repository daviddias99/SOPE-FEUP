#include <stdio.h>

#define CHUNK_SIZE 64

int main(int argc, char* argv[]){

    if(argc < 3){

        printf("Invalid number of arguments. \n");
        return -1;
    }


    char chunk[CHUNK_SIZE];

    FILE* sourceFile = fopen(argv[1],"r");
    FILE* destFile = fopen(argv[2],"w");

    size_t nRead;

    if((sourceFile == NULL) || (destFile == NULL))
        return -2;

    while( (nRead = fread(chunk,sizeof(char),CHUNK_SIZE,sourceFile)) != 0) {
        fwrite(chunk,sizeof(char),nRead,destFile);

    fclose(sourceFile);
    fclose(destFile);


    return 0;
}