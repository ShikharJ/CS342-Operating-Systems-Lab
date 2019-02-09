#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

//For computing factorial
int factorial(int i){
    if (i == 1 || i == 0){
        return 1;
    }
    return i * factorial(i - 1);
}

//Please compile as gcc -o file2 file2.c
int main(int argc, char *argv[])
{
    if (argc < 3){
        printf("You have not entered the required number of arguments!\n");
        return 0;
    }

    float x = atof(argv[0]), ans = 1;
    int n = atoi(argv[1]), j = atoi(argv[2]), i;        //Taking input in required format
    float y = x;

    for (i = 1; i <= n; i++){
        ans += x / factorial(i);                        //Calculating result
        x *= x;
    }

    printf("Child (PID = %d) : For x = %lf the first %d terms yields ", j, y, n);
    printf("%f\n", ans);
    return 0;
}