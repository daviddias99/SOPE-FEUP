#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  int nRep = 1;

  if(argc > 2)
    nRep = atoi(argv[2]);

  for(int i = 0; i < nRep;i++){

    printf("Hello %s ! \n", argv[1]);
  }
  
  return -1;
}
