#include <stdio.h>
#include <stdlib.h>

// A comparator function used by qsort.
int compare(const void *a, const void *b)
{ 
    return (*(int *)a - *(int *)b);
}

int main(void)
{
    // Read from file.
    FILE *fp = fopen("work_queue.txt", "r");
    int A[1000];
    int B[1000];
    int element, n = 0;

    // Input the elements.
    while (fscanf(fp, "%d", &element) > 0)
    {
        A[n] = element;
        B[n] = element;
        n++;
    }

    // FCFS Implementation
    int fcfs = 0;
    int start = 50;

    for (int i = 0; i < n; i++)
    {
        fcfs += abs(A[i] - start);
        start = A[i];
    }

    // SCAN Implementation
    int scan = 0;
    int index = -1;
    int flag = 0;
    start = 50;
    // Sort the array for comparison.
    qsort(B, n, sizeof(int), compare);

    for (int i = n - 1; i >= 0; i--)
    {
        if (B[i] > start)
        {
            continue;
        } else
        {
            if (flag == 0)
            {
                index = i;
                flag = 1;
            }
            scan += abs(start - B[i]);
            start = B[i];
        }
    }

    // Add the head movement to left end and back.
    scan += 2 * start;

    for (int i = 0; i < n; i++)
    {
        if (i <= index)
        {
            continue;
        } else
        {
            scan += abs(B[i] - start);
            start = B[i];
        }
    }

    // C-SCAN Implementation
    int c_scan = 0;
    flag = 0;
    index = -1;
    start = 50;

    for (int i = n - 1; i >= 0; i--)
    {
        if (B[i] > start)
        {
            continue;
        } else
        {
            if (flag == 0)
            {
                index = i;
                flag = 1;
            }
            c_scan += abs(start - B[i]);
            start = B[i];
        }
    }

    // Add the head movement to the left end and shift to right end.
    c_scan += start + 1;
    start = 199;

    for (int i = n - 1; i > index; i--)
    {
        c_scan += abs(B[i] - start);
        start = B[i];
    }

    // SSTF Implementation
    int sstf = 0;
    flag = 0;
    index = -1;
    start = 50;

    if (B[0] >= start)      // In case the all the blocks are larger than starting block.
    {
        for (int i = 0; i < n; i++)
        {
            sstf += B[i] - start;
            start = B[i];
        }
    } else if (B[n - 1] <= start)       // In case the all the blocks are smaller than starting block.
    {
        for (int i = n - 1; i >= 0; i--)
        {
            sstf += start - B[i];
            start = B[i];
        }
    } else              // General case.
    {
        for (int i = 0; i < n; i++)
        {
            if (B[i] < start)
            {
                continue;
            } else
            {
                if (flag == 0)
                {
                    index = i;
                    flag = 1;
                }
            }
        }

        int count = n;
        int left = index - 1;
        int right =  index;
        int left_flag = 1;
        int right_flag = 1;
        while (count > 0)
        {
            if ((abs(B[right] - start) >= abs(B[left] - start)) && (left_flag == 1))
            {
                count--;
                sstf += abs(B[left] - start);
                start = B[left];
                left -= 1;
                if (left < 0)
                {
                    left_flag = 0;
                }
            } else if (right_flag == 1)
            {
                count--;
                sstf += abs(B[right] - start);
                start = B[right];
                right += 1;
                if (right == n)
                {
                    right_flag = 0;
                }
            }
        }
    }

    // Print the results for the different disk scheduling algorithms.
    printf("-------Results-------\n");
    printf("--------FCFS--------\n");
    printf("The Total Head Movement For FCFS Is: %d\n", fcfs);
    printf("The Total Seek Time For FCFS Is: %d ms\n\n", fcfs * 5);

    printf("--------SCAN--------\n");
    printf("The Total Head Movement For SCAN Is: %d\n", scan);
    printf("The Total Seek Time For SCAN Is: %d ms\n\n", scan * 5);

    printf("-------C-SCAN-------\n");
    printf("The Total Head Movement For C-SCAN Is: %d\n", c_scan);
    printf("The Total Seek Time For C-SCAN Is: %d ms\n\n", c_scan * 5);

    printf("--------SSTF--------\n");
    printf("The Total Head Movement For SSTF Is: %d\n", sstf);
    printf("The Total Seek Time For SSTF Is: %d ms\n\n", sstf * 5);
    
    return 0;
}