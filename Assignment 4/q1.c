#include<stdio.h>
#include<pthread.h>

void *printer()
{
    pthread_detach(pthread_self());
    printf("CSE OS LAB, by Thread ID: %lu\n", pthread_self());
    pthread_exit(NULL);
}

int main()
{
    pthread_t t, u, v;          // Create 3 threads

    if(pthread_create(&t, NULL, printer, NULL))         // Error Checking
    {
        fprintf(stderr, "Error Creating Thread!\n");
        return 1;
    }

    if(pthread_create(&u, NULL, printer, NULL))         // Error Checking
    {
        fprintf(stderr, "Error Creating Thread!\n");
        return 1;
    }

    if(pthread_create(&v, NULL, printer, NULL))         // Error Checking
    {
        fprintf(stderr, "Error Creating Thread!\n");
        return 1;
    }

    pthread_exit(NULL);         // Exit Main Thread
    return 0;
}