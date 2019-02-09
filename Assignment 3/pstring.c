#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

//Please compile as gcc -o pstring pstring.c
int main(int argc, char *argv[])
{
	if (argc < 2){                     //Error checking
        printf("You have not entered the required number of arguments!\n");
        return 0;
    }

    pid_t child_process = fork();       //Fork

    if (child_process < 0)              //Error checking
    {
        fprintf(stderr, "Fork Failed!");
        return 1;
    }
    else if (child_process > 0)         //Parent process
    {
        wait(NULL);
        exit(0);
    }
    else                                    //Child process
    {
        execlp("xterm", "xterm", "-hold", "-e", "./dstring", argv[1], argv[1], NULL);
        exit(0);
    }

    return 0;
}