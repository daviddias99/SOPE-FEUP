// PROGRAMA p5a.c

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
  int fd;
  char *text1="AAAAA";
  char *text2="BBBBB";

  fd = open("f1.txt",O_CREAT|O_EXCL|O_TRUNC|O_WRONLY|O_SYNC,0600);
  getchar();
  printf("%d \n",(int)write(fd,text1,5));
  getchar();
  printf("%d \n",(int)write(fd,text2,5));
  close(fd);
  return 0;
}

