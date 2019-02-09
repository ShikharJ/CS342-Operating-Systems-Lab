#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

int main()
{
    int fd[2];              //File descriptor
    int p = pipe(fd);       //Pipe

    if (p == -1)            //Error checking
    {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }

    pid_t child_process = fork();       //Fork

    if (child_process < 0)              //Error checking
    {
        fprintf(stderr, "Fork Failed!");
        return 1;
    }
    else if (child_process > 0)         //Parent process
    {
        char input_str[] = "Hello World of Piping!";
        close(fd[0]);
        write(fd[1], input_str, strlen(input_str) + 1);
        close(fd[1]);
        exit(0);
    }
    else                                //Child process
    {
        close(fd[1]);
        char passed_str[100];
        read(fd[0], passed_str, 100);
        printf("Passed Message: %s\n", passed_str);
        close(fd[0]);
        exit(0);
    }
    return 0;
}