#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    DIR *dirp;
    struct dirent *direntp;
    struct stat stat_buf;
    char *str;
    char name[257];

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s dir_name\n", argv[0]);
        exit(1);
    }

    if ((dirp = opendir(argv[1])) == NULL)
    {
        perror(argv[1]);
        exit(2);
    }

    while ((direntp = readdir(dirp)) != NULL)
    {   
        sprintf(name, "%s/%s", argv[1], direntp->d_name); // <----- NOTAR
        if (lstat(name, &stat_buf) == -1) // testar com stat()
        {
            perror("lstat ERROR");
            exit(3);
        }
        if (S_ISREG(stat_buf.st_mode))
            str = "regular";
        else if (S_ISDIR(stat_buf.st_mode))
            str = "directory";
        else
            str = "other";
        printf("%-25s - %-15s |%-15d | %d\n", direntp->d_name, str, (int)stat_buf.st_ino, (int)stat_buf.st_size);
    }

    closedir(dirp);
    exit(0);
}
