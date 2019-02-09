#include<stdio.h>
#include<stdlib.h>

//Please compile as gcc -o server server.c
int main(int argc, char *argv[])
{
    if (argc < 3){
        printf("You have not entered the required number of arguments!\n");
        return 0;
    }

    char *a = argv[0];                  //Taking inputs and operator
    char *oper = argv[1];
    char *b = argv[2];
    int i = atoi(a);
    int j = atoi(b);

    if (oper[0] == '+')                 // Printing the result
    {
        printf("%d\n", i + j);
    } else
    {
        printf("%d\n", i - j);
    }
    return 0;
}