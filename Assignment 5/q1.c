#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

// Predefined macros.
#define N 5
#define LEFT (philosopher + 4) % N
#define RIGHT (philosopher + 1) % N

// Predefined states.
const int thinking = 2;
const int hungry = 1;
const int eating = 0;

// Predefined buffers for storing information.
int state[N];
int philosophers[N] = {0, 1, 2, 3, 4};
sem_t mutex;

// Single graph for allocation and request tracking.
int resource_graph[2 * N][2 * N] = {};
int visited[2 * N] = {};

// Function for calculating the minimum of two numbers.
int min(int a, int b)
{
    if (a < b)
    {
        return a;
    }

    return b;
}

// Function for checking whether the right fork is available, and filing a request for it.
void test_right(int philosopher)
{
    resource_graph[philosopher][N + philosopher] = 1;
    if (state[philosopher] == hungry && state[RIGHT] != eating)
    {
        // State that the philosopher is eating.
        state[philosopher] = eating;
        sleep(1);
        printf("Philosopher %d takes fork %d (right).\n", philosopher + 1, philosopher + 1);
        resource_graph[N + philosopher][philosopher] = 1;
        resource_graph[philosopher][N + philosopher] = 0;
        printf("Philosopher %d is eating.\n", philosopher + 1);
    }

    return ;
}

// Function for checking whether the left fork is available, and filing a request for it.
void test_left(int philosopher)
{
    resource_graph[philosopher][N + LEFT] = 1;
    if (state[philosopher] == hungry && state[LEFT] != eating)
    {
        sleep(1);
        printf("Philosopher %d takes fork %d (left).\n", philosopher + 1, LEFT + 1);
        resource_graph[N + LEFT][philosopher] = 1;
        resource_graph[philosopher][N + LEFT] = 0;
        test_right(philosopher);
    }

    return ;
}

// Function for taking up the forks.
void take_fork(int philosopher)
{
    sem_wait(&mutex);

    // State that the philosopher is hungry.
    state[philosopher] = hungry;

    printf("Philosopher %d is hungry.\n", philosopher + 1);

    // Eat if the left neighbour is not eating.
    test_left(philosopher);
    sem_post(&mutex);

    sleep(1);
    return ;
}
 
// Function for putting down the forks.
void put_fork(int philosopher)
{ 
    sem_wait(&mutex);

    // State that the philosopher is thinking.
    state[philosopher] = thinking;

    printf("Philosopher %d putting fork %d (left) and %d (right) down.\n", philosopher + 1, LEFT + 1, philosopher + 1);
    resource_graph[N + LEFT][philosopher] = 0;
    resource_graph[N + philosopher][philosopher] = 0;
    resource_graph[philosopher][N + LEFT] = 0;
    resource_graph[philosopher][N + philosopher] = 0;
    printf("Philosopher %d is thinking.\n", philosopher + 1);

    test_left(LEFT);
    test_left(RIGHT);

    sem_post(&mutex);
    return ;
}

// Run the philosopher life cycle indefinitely.
void *philosopher(void *num) 
{ 
    while (1)
    {
        int *i = num;
        sleep(1);
        take_fork(*i);
        sleep(1);
        put_fork(*i);
    }

    return NULL;
}

// Function for preempting a philosophers forks.
void release_resources(int philosopher)
{
    printf("Parent preempts philosopher %d.\n", philosopher + 1);

    // State that the philosopher is thinking.
    state[philosopher] = thinking;

    printf("Philosopher %d putting fork %d (left) and %d (right) down.\n", philosopher + 1, LEFT + 1, philosopher + 1);
    resource_graph[N + LEFT][philosopher] = 0;
    resource_graph[N + philosopher][philosopher] = 0;
    resource_graph[philosopher][N + LEFT] = 0;
    resource_graph[philosopher][N + philosopher] = 0;
    printf("Philosopher %d is thinking.\n", philosopher + 1);

    test_left(LEFT);
    test_left(RIGHT);

    return ;
}

// Function for finding a loop in the resource graph.
int dfs(int i)
{
    int j;
    visited[i] = 1;
    
    for(j = 0; j < 2 * N; j++)
    {
        if (visited[j] == 1 && resource_graph[i][j] == 1)
        {
            return min(j, i);
        }

        if (visited[j] == 0 && resource_graph[i][j] == 1)
        {
            return dfs(j);
        }
    }
    return -1;
}

// Function for calling the depth-first search.
int loop_checking()
{
    int k, i;
    for (i = 0; i < 2 * N; i++)
    {
        memset(visited, 0, sizeof(visited));
        k = dfs(i);
        if (k >= 0)
        {
            break;
        }
    }
    return k;
}

// Function for checking the deadlock condition and preempting the required philosopher.
void deadlock_check()
{
    int k = loop_checking();

    if (k >= 0)
    {
        printf("Parent detects deadlock, going to initiate recovery.\n");
        release_resources(k);
    }

    return ;
}

// Function for printing the allocation graph.
void print_allocation_graph()
{
    int i, j;
    printf("The Allocation Graph: (Resources Along Rows and Philosophers Along Columns)\n");
    for (i = N; i < 2 * N; i++){
        for (j = 0; j < N; j++){
            printf("%d ", resource_graph[i][j]);
        }
        printf("\n");
    }
}

// Function for printing the request graph.
void print_request_graph()
{
    int i, j;
    printf("The Request Graph: (Philosophers Along Rows and Resources Along Columns)\n");
    for (i = 0; i < N; i++){
        for (j = N; j < 2 * N; j++){
            printf("%d ", resource_graph[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int i;
    pthread_t thread_id[N];

    // Initialize the semaphores.
    sem_init(&mutex, 0, 1);

    for (i = 0; i < N; i++)
    {
        // Create philosopher processes.
        pthread_create(&thread_id[i], NULL, philosopher, &philosophers[i]);
        printf("Philosopher %d is thinking.\n", i + 1);
    }

    // Check for a deadlock after every fixed interval of time.
    while (1)
    {
        sem_wait(&mutex);
        deadlock_check();
        print_allocation_graph();
        print_request_graph();
        sem_post(&mutex);
        sleep(1);
    }

    // Join threads after execution.
    for (i = 0; i < N; i++)
    {
        pthread_join(thread_id[i], NULL);
    }

    return 0;
}