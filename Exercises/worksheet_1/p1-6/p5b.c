#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Get "USER" environment variable

int main(int argc, char* argv[], char* envp[])
{
  char* name;

    int i = 0;
    char* currPtr = envp[i];

    while(currPtr != NULL){

        if(strncmp(currPtr,"USER=",5) == 0){
            
            /*

            // SUBSTRING METHOD, LESS EFFICIENT

            name = malloc(sizeof(char)*MAX_NAME_LENGTH);

            int j = 0;

            char currLetter = currPtr[j+5];

            while(currLetter != '\0'){

                name[j] = currLetter;
                j++;
                currLetter = currPtr[j+5];
            }
            */

            currPtr += 5;
            name = currPtr;
            break;
        }

        i++;
        currPtr = envp[i];
    }


    printf("Hello %s ! \n", name);
  
  
  return -1;
}
