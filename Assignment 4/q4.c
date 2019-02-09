#include<stdio.h>
#include<pthread.h>

// Function for printing even numbers
void *printer()
{
    for (int i = 1; i <= 10000; i++)
    {
        printf("The Additional Thread Prints: %d\n", 2 * i);
    }
    pthread_exit(NULL);
}

// Function for printing odd numbers
void printer2()
{
    for (int i = 0; i < 10000; i++)
    {
        printf("The Main Thread Prints: %d\n", (2 * i) + 1);
    }
}

int main()
{
    pthread_t a;        // Create an additional thread

    if(pthread_create(&a, NULL, printer, NULL))         // Error Checking
    {
        fprintf(stderr, "Error Creating Thread!\n");
        return 1;
    }
    printer2();         // Print odd numbers

    pthread_exit(NULL);         // Exit Main Thread
    return 0;
}