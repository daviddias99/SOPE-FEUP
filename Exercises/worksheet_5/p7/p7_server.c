#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define READ 0
#define WRITE 1

int main(int argc, char *argv[])
{

    int reqFD = open("/tmp/fifo_req", O_WRONLY);
    int ansFD = open("/tmp/fifo_ans", O_RDONLY);

    int numA, numB;
    scanf("%d%d", &numA, &numB);

    write(reqFD, &numA, sizeof(int));
    write(reqFD, &numB, sizeof(int));

    while (true)
    {

        char currType;
        int nRead = read(ansFD, &currType, sizeof(char));

        if (nRead == 0)
            break;

        if (currType == 'i')
        {

            int currRes;
            read(ansFD, &currRes, sizeof(int));
            printf("%d \n", currRes);
        }
        else if (currType == 'f')
        {

            float currRes;
            read(ansFD, &currRes, sizeof(float));
            printf("%f \n", currRes);
        }
        else if (currType == 'E')
        {

            float currRes;
            read(ansFD, &currRes, sizeof(float));
            printf("INVALIDO \n");
        }
    }

    return 0;
}