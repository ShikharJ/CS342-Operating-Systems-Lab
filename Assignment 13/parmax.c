#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

// Array For Storing Random Integers
int A[101];

// Function For Calculating The Maximum Of Two Integers
int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

// Recursive Function For Calculating The Maximum Of A Range In Array
void create_process(int l, int r)
{
    int status;

    if (r - l >= 10)
    {
        // We Create Two Forks
        int pid1, pid2;
        pid1 = fork();

        if (pid1 == -1)                 // Error Checking
        {
            fprintf(stderr, "Left Fork Failed!\n");
        } else if (pid1 == 0)
        {
            // Left Fork Child
            r = ((l + r) / 2);          // Calculate The Upper Limit
            create_process(l, r);       // Call Recursive Function
        } else
        {   // Inside Parent
            pid2 = fork();

            if (pid2 == -1)             // Error Checking
            {
                fprintf(stderr, "Right Fork Failed!\n");
            } else if (pid2 == 0)
            {
                // Right Fork Child
                l = ((l + r) / 2) + 1;      // Calculate The Upper Limit
                create_process(l, r);       // Call Recursive Function
            } else
            {
                waitpid(pid1, &status, 0);                      // Wait On The Left Fork Child
                int max_left = status >> 8;                     // Get The Returned Value
                waitpid(pid2, &status, 0);                      // Wait On The Right Fork Child
                int max_right = status >> 8;                    // Get The Returned Value
                int maximum = max(max_left, max_right);         // Find The Maximum Of Children
                printf("PID = %d, Parent PID = %d, L = %d, R = %d, Maximum Value = %d\n", getpid(), getppid(), l, r, maximum);      // Print The PID, Parent PID, Left Limit, Right Limit And The Maximum Value
                exit(maximum);                                  // Exit With The Maximum Value
            }
        }
    } else
    {
        // In Case The Number Of Elements Is Less Than 10
        int maximum = -1;
        for (int i = l; i <= r; i++)
        {
            // Find The Maximum In Single Iteration
            maximum = max(A[i], maximum);
        }

        // Print The PID, Parent PID, Left Limit, Right Limit And The Maximum Value
        printf("PID = %d, Parent PID = %d, L = %d, R = %d, Maximum Value = %d\n", getpid(), getppid(), l, r, maximum);
        exit(maximum);          // Exit With The Maximum Value
    }
}

int main(int argc, char *argv[])
{
    // Error Checking
    if (argc <= 1){
        printf("You have not entered the required number of arguments!\n");
        return 0;
    }

    srand(time(NULL));          // Setting The Random Seed
    int n = atoi(argv[1]);      // Parsing The Command Line Argument
    int status;

    // Printing The Original Array
    printf("Unsorted Array:\n");
    for (int i = 0; i < n; i++)
    {
        A[i] = rand() % 128;
        printf("%d ", A[i]);
    }
    printf("\n\n");

    // Initial Fork
    int pid;
    pid = fork();

    if (pid == -1){
        fprintf(stderr, "Fork Failed!\n");
    } else if (pid == 0){
        // Call The Recursive Function Inside The Child Process.
        create_process(0, n - 1);
    } else {
        // Wait For The Child To Finish And Read The Value Passed On Exit
        waitpid(pid, &status, 0);
        int maximum = status >> 8;
        printf("The Maximum Value In The Array Is: %d\n", maximum);
    }

    return 0;
}