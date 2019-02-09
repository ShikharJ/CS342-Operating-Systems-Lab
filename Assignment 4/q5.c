#include<stdio.h>
#include<pthread.h>

int count = 0;          // For keeping counts
int truth = 1;          // For infinite while loop till completion
#define COUNT_DONE 19999        // Numbers to be printed
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;

// Function for printing even numbers
void *printer()
{
    while(truth) {                          // Infinite while loop
        pthread_mutex_lock(&count_mutex);   // Mutex Lock
        if (count % 2 == 0) {
            pthread_cond_wait(&condition_var, &count_mutex);
        }
        count++;
        printf("Counter Value In Additional Thread: %d\n", count);     // Printing Count
        pthread_cond_signal(&condition_var);
        if (count >= COUNT_DONE)
        {
            pthread_mutex_unlock(&count_mutex);     // Exiting thread
            return NULL;
        }
        pthread_mutex_unlock(&count_mutex);         // Mutex Unlock
    }
    
}

// Function for printing odd numbers
void printer2()
{
    while(truth) {                          // Infinite while loop
        pthread_mutex_lock(&count_mutex);   // Mutex Lock
        if (count % 2 != 0) {
            pthread_cond_wait(&condition_var, &count_mutex);
        }
        count++;
        printf("Counter Value In Main Thread: %d\n", count);        // Printing Count
        pthread_cond_signal(&condition_var);
        if (count >= COUNT_DONE)
        {
            pthread_mutex_unlock(&count_mutex);     // Exiting Thread
            return ;
        }
        pthread_mutex_unlock(&count_mutex);         // Mutex Unlock
    }
}

int main()
{
    pthread_t thread1;
    pthread_create(&thread1, NULL, printer, NULL);
    printer2();
    pthread_join(thread1, NULL);
    return 0;
}

