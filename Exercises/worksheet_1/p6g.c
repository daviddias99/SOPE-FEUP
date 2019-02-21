// PROGRAMA p6g.c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>


bool checkExtension(char* string){

    char currChar = *string;
    char* currPtr = string + 1;

    while(currChar != '\0'){

        currPtr++;
        currChar = *currPtr;
    }

    currPtr -= 4;
    if(strcmp(".txt",currPtr) == 0)
        return true;
    else
        return false;

}

#define BUF_LENGTH 256
int main(int argc, char* argv[])
{
    FILE *src, *dst;
    char buf[BUF_LENGTH];
    char* srcFileName;
    char* dstFileName;

    if(argc != 3){

        errno = EINVAL;
        perror("usage: nome_do_executável file1 file2 \n");
        exit(3);
    }

    srcFileName = argv[1];
    dstFileName = argv[2];

    if(!checkExtension(srcFileName)){

         errno = EINVAL;
        perror("(5)usage: nome_do_executável file1 file2 \n");
        exit(5);
    }
    if(!checkExtension(dstFileName)){

         errno = EINVAL;
        perror("(6)usage: nome_do_executável file1 file2 \n");
        exit(6);
    }

    if ((src = fopen(srcFileName, "r")) == NULL)
    {
        printf("%s \n",strerror(errno));
        perror("Unable to open reading file \n");
        
        exit(1);
    }
    if ((dst = fopen(dstFileName, "w")) == NULL)
    {
        printf("%s \n",strerror(errno));
        perror("Unable to open writing file \n");
        exit(2);
    }
    while ((fgets(buf, BUF_LENGTH, src)) != NULL)
    {
        fputs(buf, dst);
    }
    fclose(src);
    fclose(dst);
    exit(0); // zero é geralmente indicativo de "sucesso"
}