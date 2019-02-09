#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

int main()
{
    char a[100], oper[100], b[100];             //Storing input and operation
    printf("Enter The Operation: ");
    scanf("%s %s %s", a, oper, b);

    pid_t child_process = fork();               //Fork
    pid_t status;

    if (child_process < 0)                      //Error checking
    {
        fprintf(stderr, "Fork Failed!");
        return 1;
    }
    else if (child_process > 0)                 //Parent process
    {
        wait(&status);
        exit(0);
    }
    else
    {
        execl("./server", a, oper, b, NULL);    //Calling server.c
        exit(0);
    }
    return 0;
}