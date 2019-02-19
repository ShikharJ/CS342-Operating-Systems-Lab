#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Read from file.
    FILE *fp = fopen("pages.txt", "r");
    int n;
    // Input the number of frames.
    while (fscanf(fp, "%d", &n) > 0)
    {
        printf("\nNumber of Frames: %d\n", n);

        // Create and initialize FIFO and LRU buffers.
        int A[n];
        int B[n];
        for (int i = 0; i < n; i++)
        {
            A[i] = 0;
            B[i] = 0;
        }

        int element, endA = 0, endB = 0, faultsA = 0, faultsB = 0;
        // Input the elements.
        while (fscanf(fp, "%d", &element) > 0 && element != -1)
        {
            printf("The Element Entered: %d\n", element);
            int foundA = -1;
            int foundB = -1;
            for (int i = 0; i < n; i++)
            {
                // Search the element in FIFO queue.
                if (A[i] == element)
                {
                    foundA = 1;
                    break;
                } else
                {
                    continue;
                }
            }

            for (int i = 0; i < n; i++)
            {
                // Search the element in LRU cache.
                if (B[i] == element)
                {
                    foundB = i;
                    break;
                } else
                {
                    continue;
                }
            }

            if (foundA == -1)
            {
                // Enter the element into the FIFO queue in case page fault occurs.
                printf("Fault Occurred in FIFO Queue! \n");
                faultsA += 1;
                if (endA < n)
                {
                    A[endA] = element;
                    endA++;
                } else
                {
                    for (int i = 1; i < n; i++)
                    {
                        A[i - 1] = A[i];
                    }
                    A[endA - 1] = element;
                }
            }

            if (foundB != -1)
            {
                // Update the LRU cache if the element is found.
                for (int i = foundB + 1; i < n; i++)
                {
                    B[i - 1] = B[i];
                }
                B[endB - 1] = element;
            } else
            {
                // Enter the element into the LRU cache in case page fault occurs.
                printf("Fault Occurred in LRU Cache! \n");
                faultsB += 1;
                if (endB < n)
                {
                    B[endB] = element;
                    endB++;
                } else
                {
                    for (int i = 1; i < n; i++)
                    {
                        B[i - 1] = B[i];
                    }
                    B[endB - 1] = element;
                }
            }

            // Print the contents of the FIFO queue and LRU cache.
            printf("The Current Contents of the FIFO Queue:\n");
            for (int i = 0; i < n; i++)
            {
                printf("%d ", A[i]);
            }
            printf("\n\n");

            printf("The Current Contents of the LRU Cache:\n");
            for (int i = 0; i < n; i++)
            {
                printf("%d ", B[i]);
            }
            printf("\n\n");
        }
        // Print the statistics.
        printf("Using %d frames, the reference string yielded:\n", n);
        printf("Scheme: FIFO           #Faults: %d\n", faultsA);
        printf("Scheme: LRU            #Faults: %d\n", faultsB);
    }
    return 0;
}