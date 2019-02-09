#include<stdio.h>
#include<pthread.h>

int p = 5;

// Function for desired effect
void *printer()
{
    static int q = 10;
    int r = 15;
    pthread_detach(pthread_self());
    unsigned long id = pthread_self();
    printf("This Is Thread ID: %lu, Incrementing All Variables\n", id);
    printf("Initial Value Of Global Variable: %d\n", p);
    printf("Initial Value Of Static Variable: %d\n", q);
    printf("Initial Value Of Local Variable: %d\n", r);

    p += 1;
    q += 1;
    r += 1;

    printf("ID: %lu Reports Global Variable As: %d\n", id, p);
    printf("ID: %lu Reports Static Variable As: %d\n", id, q);
    printf("ID: %lu Reports Local Variable As: %d\n", id, r);
    pthread_exit(NULL);
}

int main()
{
    pthread_t a, b, c, d, e;            // Creating 5 threads

    if(pthread_create(&a, NULL, printer, NULL))         // Error Checking
    {
        fprintf(stderr, "Error Creating Thread!\n");
        return 1;
    }

    if(pthread_create(&b, NULL, printer, NULL))         // Error Checking
    {
        fprintf(stderr, "Error Creating Thread!\n");
        return 1;
    }

    if(pthread_create(&c, NULL, printer, NULL))         // Error Checking
    {
        fprintf(stderr, "Error Creating Thread!\n");
        return 1;
    }

    if(pthread_create(&d, NULL, printer, NULL))         // Error Checking
    {
        fprintf(stderr, "Error Creating Thread!\n");
        return 1;
    }

    if(pthread_create(&e, NULL, printer, NULL))         // Error Checking
    {
        fprintf(stderr, "Error Creating Thread!\n");
        return 1;
    }

    pthread_exit(NULL);         // Exit Main Thread
    return 0;
}