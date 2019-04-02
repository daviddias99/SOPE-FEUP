#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define READ 0
#define WRITE 1

int main(int argc, char *argv[])
{

    if (argc != 3)
        return -1;

    char *dir = argv[1];
    char *arg = argv[2];

    int fd1[2];
    pipe(fd1);

    pid_t PID1 = fork();

    if (PID1 == 0)
    {

        close(fd1[READ]);
        dup2(fd1[WRITE], STDOUT_FILENO);
        execlp("ls", "ls", dir, NULL);
    }
    else
    {

        close(fd1[WRITE]);
        int fd2[2];
        pipe(fd2);

        pid_t PID2 = fork();

        if (PID2 == 0)
        {

            close(fd2[READ]);

            dup2(fd1[READ], STDIN_FILENO);
            dup2(fd2[WRITE], STDOUT_FILENO);
            execlp("grep", "grep", arg, NULL);
        }
        else
        {
            close(fd1[READ]);
            close(fd2[WRITE]);

            dup2(fd2[READ], STDIN_FILENO);
            execlp("sort", "sort", NULL);
        }
    }
}