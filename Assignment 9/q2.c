#include <stdio.h>
#include <stdlib.h>

// Variables for holding the number of processes and resources.
int p, r;

// Function for calculating the need matrix and printing it to console.
void calculate_need(int need[p][r], int maximum[p][r], int allocation[p][r])
{
    printf("Contents Of The Need Matrix:\n");
    for (int i = 0 ; i < p ; i++)
    {
        for (int j = 0 ; j < r ; j++)
        {
            need[i][j] = maximum[i][j] - allocation[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

// Function for checking the safe state and calculating the safe sequence.
int is_safe(int processes[p], int available[r], int maximum[p][r], int allocation[p][r], int mode)
{ 
    int need[p][r];
    int safe_sequence[p];
    int work[r];
    int finish[p];

    // Calculate the need matrix.
    calculate_need(need, maximum, allocation);

    // Initialize the remaining matrices.
    for (int i = 0; i < p; i++)
    {
        finish[i] = 0;
    }

    for (int i = 0; i < r; i++){
        work[i] = available[i];
    }

    int count = 0; 
    while (count < p) 
    {
        // Variable for indication of the presence of a safe sequence.
        int found = -1;
        for (int i = 0; i < p; i++)
        {
            // If the process is finished, continue to the next, else do the following.
            if (finish[i] == 0) 
            {
                int j; 
                for (j = 0; j < r; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        break; 
                    }
                }

                // If the process requirements can be afforded by the system.
                if (j == r)
                {
                    for (int k = 0 ; k < r; k++)
                    {
                        work[k] += allocation[i][k];
                    }

                    // Add the process to the safe sequence.
                    safe_sequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        // Print if the safe sequence is not found.
        if (found == -1)
        {
            printf("System Is Not In A Safe State!\n");
            if (mode == 1)
            {
                printf("Part 3: The Request Cannot Be Granted!\n");
            }
            return 0;
        }
    }

    // Print if the safe sequence is found.
    printf("System Is In A Safe State!\n");
    if (mode == 1)
    {
        printf("Part 3: The Request Can Be Granted!\n");
    }
    printf("Safe Sequence Is: "); 
    for (int i = 0; i < p; i++)
    {
        printf("%d ", safe_sequence[i]);
    }
    printf("\n");

    return 1;
}

int main() 
{
    int k;
    char c;

    // Give the choice to the user.
    printf("Welcome To Banker's Algorithm\n");
    printf("Enter A Choice:\n");
    printf("1) User Input\n");
    printf("2) Sample Input\n");
    scanf("%d%c", &k, &c);

    if (k == 1)
    {
        // Run the input mode.
        // Input the number of processes.
        printf("Enter The Number Of Processes: ");
        scanf("%d%c", &p, &c);

        int processes[p];
        for (int i = 0; i < p; i++)
        {
            processes[i] = i;
        }

        // Input the number of resources.
        printf("Enter The Number Of Resources: ");
        scanf("%d%c", &r, &c);

        // Input the available resource matrix.
        int available[r];
        printf("Enter The Available Resource Matrix:\n");
        for (int i = 0; i < r; i++)
        {
            scanf("%d%c", &k, &c);
            available[i] = k;
        }

        // Input the maximum resource matrix.
        int maximum[p][r];
        printf("Enter The Maximum Resource Matrix:\n");
        for (int i = 0; i < p; i++)
        {
            for (int j = 0; j < r; j++)
            {
                scanf("%d%c", &k, &c);
                maximum[i][j] = k;
            }
        }

        // Input the allocation resource matrix.
        int allocation[p][r];
        printf("Enter The Allocation Resource Matrix:\n");
        for (int i = 0; i < p; i++)
        {
            for (int j = 0; j < r; j++)
            {
                scanf("%d%c", &k, &c);
                allocation[i][j] = k;
            }
        }

        // Check for the safe state.
        is_safe(processes, available, maximum, allocation, 0);

        // Input the request matrix for P1.
        printf("Enter The Request Matrix For P1: ");
        for (int i = 0; i < r; i++)
        {
            scanf("%d%c", &k, &c);
            available[i] -= k;
            allocation[1][i] += k;
        }

        // Check if the request can be granted.
        is_safe(processes, available, maximum, allocation, 1);
    } else
    {
        // Run the sample mode.
        p = 5;
        r = 4;

        int processes[p];
        int available[r];
        int maximum[p][r];
        int allocation[p][r];

        for (int i = 0; i < p; i++)
        {
            processes[i] = i;
        }

        available[0] = 1;
        available[1] = 5;
        available[2] = 2;
        available[3] = 0;

        maximum[0][0] = 0;
        maximum[0][1] = 0;
        maximum[0][2] = 1;
        maximum[0][3] = 2;
        maximum[1][0] = 1;
        maximum[1][1] = 7;
        maximum[1][2] = 5;
        maximum[1][3] = 0;
        maximum[2][0] = 2;
        maximum[2][1] = 3;
        maximum[2][2] = 5;
        maximum[2][3] = 6;
        maximum[3][0] = 0;
        maximum[3][1] = 6;
        maximum[3][2] = 5;
        maximum[3][3] = 2;
        maximum[4][0] = 0;
        maximum[4][1] = 6;
        maximum[4][2] = 5;
        maximum[4][3] = 6;

        allocation[0][0] = 0;
        allocation[0][1] = 0;
        allocation[0][2] = 1;
        allocation[0][3] = 2;
        allocation[1][0] = 1;
        allocation[1][1] = 0;
        allocation[1][2] = 0;
        allocation[1][3] = 0;
        allocation[2][0] = 1;
        allocation[2][1] = 3;
        allocation[2][2] = 5;
        allocation[2][3] = 4;
        allocation[3][0] = 0;
        allocation[3][1] = 6;
        allocation[3][2] = 3;
        allocation[3][3] = 2;
        allocation[4][0] = 0;
        allocation[4][1] = 0;
        allocation[4][2] = 1;
        allocation[4][3] = 4;

        // Check for the safe state.
        is_safe(processes, available, maximum, allocation, 0);

        available[0] = 1;
        available[1] = 1;
        available[2] = 0;
        available[3] = 0;

        allocation[1][0] = 1;
        allocation[1][1] = 4;
        allocation[1][2] = 2;
        allocation[1][3] = 0;

        // Check if the request can be granted.
        is_safe(processes, available, maximum, allocation, 1);
    }

    return 0;
}