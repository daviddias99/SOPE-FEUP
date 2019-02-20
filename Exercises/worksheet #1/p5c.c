#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char* argv[], char* envp[])
{
    char* name;

    name = getenv("USER_NAME");
   
    printf("Hello %s ! \n", name);

  
  return -1;
}