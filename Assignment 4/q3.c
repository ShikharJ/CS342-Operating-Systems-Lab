#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

// Function for keeping the threads busy
void *busy(void *p)
{
    int *myid = (int *)p; 
    sleep(5);   
    pthread_exit(NULL);
}

int main()
{
    int i, err;
    pthread_t tid;      // Thread Creation
    
    for (i = 0; i < 5; i++)         // Create 5 threads
    {
        err = pthread_create(&tid, NULL, *busy, (void *)&tid);
        printf("Creating thread %lu\n", pthread_self()); 
        if (err != 0)                                           // Error Checking
        {
            printf("ERROR; Return Code From pthread_create() Is %lu\n", pthread_self());
        }
        else
        {
            printf("Return Code From pthread_create() Is %d\n", err);       // Print return code
           
            if (pthread_join(tid, NULL))        // Error Checking
            {
                printf("ERROR; Return Code From pthread_join() Is %lu\n", pthread_self());
            }
            else
            {
                printf("Completed Join With Thread %lu Having A Status Of %d\n", pthread_self(), pthread_join(tid, NULL));      // Print Completion
            }
        }
    }
    
    printf("Exiting Program\n");        // Signal Completion
    return 0;
}