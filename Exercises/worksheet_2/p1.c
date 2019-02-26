#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_PWD_SIZE 25

int main(){

    struct termios oldTerminal, newTerminal;
    int charCount = 0;
    char ch;
    char* asterisk = "*";
    char* password = malloc(sizeof(char)* (MAX_PWD_SIZE+1) );


    printf( "Password: ");
    fflush(stdout);

    tcgetattr(STDIN_FILENO,&oldTerminal);
    newTerminal = oldTerminal;
    newTerminal.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);

    tcsetattr(STDIN_FILENO,TCSAFLUSH,&newTerminal);
    
    while( (charCount <= MAX_PWD_SIZE)&& (read(STDIN_FILENO,&ch, 1) > 0) && (ch != '\n')){

        password[charCount] = ch;
        write(STDOUT_FILENO,asterisk,1);
        charCount++;
    }

    password[charCount] = 0;

    write(STDOUT_FILENO, "\n\nPassword: ", 12);
    write(STDOUT_FILENO, password, strlen(password));
    write(STDOUT_FILENO, "\n", 1); 

    tcsetattr(STDIN_FILENO,TCSANOW,&oldTerminal);
    free(password);
    return 0;
}