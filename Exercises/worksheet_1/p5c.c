#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Same as exercise b), but using 'getenv'

int main(int argc, char* argv[], char* envp[])
{
    char* name;

    name = getenv("USER_NAME");
   
    printf("Hello %s ! \n", name);

  
  return -1;
}