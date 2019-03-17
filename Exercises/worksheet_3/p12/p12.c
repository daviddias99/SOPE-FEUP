#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>



int main(int argc, char* argv[]){

    if(argc != 3){

        printf("usage: %s <source> <destination>\n", argv[0]);
        exit(1);
    }
   

    DIR *dirp;
    struct dirent *direntp;
    struct stat stat_buf;
    char str[257];

    if ((dirp = opendir(argv[1])) == NULL)
    {
        perror(argv[1]);
        exit(2);
    }

    while ((direntp = readdir(dirp)) != NULL)
    {
        sprintf(str, "%s/%s", argv[1], direntp->d_name); 
        if (stat(str, &stat_buf) == -1) // testar com stat()
        {
            perror("lstat ERROR");
            exit(3);
        }
        if (S_ISREG(stat_buf.st_mode)){

            if(fork() != 0){
                
                execlp("ln","ln",str,argv[2],NULL);

            } 

        }
            
    
    }

    closedir(dirp);


    return 0;
}