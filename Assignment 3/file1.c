#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

//Please compile as gcc -o file1 file1.c
int main(int argc, char *argv[])
{
    if (argc <= 2){                     //Error checking
        printf("You have not entered the required number of arguments!\n");
        return 0;
    }

    char buf[10];               //Storing child pid

    pid_t child_process = fork();       //Fork

    if (child_process < 0)              //Error checking
    {
        fprintf(stderr, "Fork Failed!");
        return 1;
    }
    else if (child_process > 0)         //Parent process
    {
        wait(NULL);
        printf("Parent (PID = %d) : Done\n", getpid());
        exit(0);
    }
    else                                    //Child process
    {
        child_process = getpid();
        sprintf(buf, "%d", child_process);
        execl("./file2", argv[1], argv[2], buf, NULL);
        exit(0);
    }
    return 0;
}