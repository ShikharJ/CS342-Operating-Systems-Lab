#include <stdio.h>
#include <stdlib.h>

// Please note that LFU cache implemented here keeps local frequencies only.
int main(void)
{
    // Read from file.
    FILE *fp = fopen("pages.txt", "r");
    int n;
    // Input the number of frames.
    while (fscanf(fp, "%d", &n) > 0)
    {
        printf("\nNumber of Frames: %d\n", n);

        // Create and initialize LRU, LFU and OPT buffers.
        int A[n];
        int B[n];
        int C[n];
        int D[n];
        int E[1000];
        for (int i = 0; i < n; i++)
        {
            A[i] = 0;
            B[i] = 0;
            C[i] = 0;
            D[i] = 0;
        }

        int element, endA = 0, endB = 0, endC = 0, faultsA = 0, faultsB = 0, faultsC = 0;
        int k = 0;
        // Input the elements.
        while (fscanf(fp, "%d", &element) > 0)
        {
            E[k] = element;
            k++;
            if (element == -1)
            {
                k--;
                break;
            }
        }

        for (int j = 0; j < k; j++)
        {
            printf("The Element Entered: %d\n", E[j]);
            int foundA = -1;
            int foundB = -1;
            int foundC = -1;
            for (int i = 0; i < n; i++)
            {
                // Search the element in LRU cache.
                if (A[i] == E[j])
                {
                    foundA = i;
                    break;
                } else
                {
                    continue;
                }
            }

            if (foundA != -1)
            {
                // Update the LRU cache if the element is found.
                for (int i = foundA + 1; i < n; i++)
                {
                    A[i - 1] = A[i];
                }
                A[endA - 1] = E[j];
            } else
            {
                // Enter the element into the LRU cache in case page fault occurs.
                printf("Fault Occurred in LRU Cache! \n");
                faultsA += 1;
                if (endA < n)
                {
                    A[endA] = E[j];
                    endA++;
                } else
                {
                    for (int i = 1; i < n; i++)
                    {
                        A[i - 1] = A[i];
                    }
                    A[endA - 1] = E[j];
                }
            }

            for (int i = 0; i < n; i++)
            {
                // Search the element in LFU cache.
                if (B[i] == E[j])
                {
                    foundB = 1;
                    C[i] += 1; 
                    break;
                } else
                {
                    continue;
                }
            }

            if (foundB == -1)
            {
                // Enter the element into the LFU cache in case page fault occurs.
                printf("Fault Occurred in LFU cache! \n");
                faultsB += 1;
                if (endB < n)
                {
                    B[endB] = E[j];
                    C[endB] = 1;
                    endB++;
                } else
                {
                    int max = 999999999;
                    int index = -1;
                    for (int i = 0; i < n; i++)
                    {
                        if (C[i] < max)
                        {
                            max = C[i];
                            index = i;
                        }
                    }
                    for (int i = index + 1; i < n; i++)
                    {
                        C[i - 1] = C[i];
                        B[i - 1] = B[i];
                    }

                    B[endB - 1] = E[j];
                    C[endB - 1] = 1;
                }
            }

            for (int i = 0; i < n; i++)
            {
                // Search the element in OPT cache.
                if (D[i] == E[j])
                {
                    foundC = 1; 
                    break;
                } else
                {
                    continue;
                }
            }

            if (foundC == -1)
            {
                // Enter the element into the OPT cache in case page fault occurs.
                printf("Fault Occurred in OPT cache! \n");
                faultsC += 1;
                if (endC < n)
                {
                    D[endC] = E[j];
                    endC++;
                } else
                {
                    int max = -1;
                    int index = -1;
                    
                    for (int i = 0; i < n; i++)
                    {
                        int local_max = -1;
                        for (int l = j + 1; l < k; l++)
                        {
                            if (E[l] == D[i])
                            {
                                local_max = l - j;
                                break;
                            } else
                            {
                                continue;
                            }
                        }
                        if (local_max == -1){
                            index = i;
                            break;
                        }
                        if (local_max > max)
                        {
                            max = local_max;
                            index = i;
                        }
                    }

                    for (int i = index + 1; i < n; i++)
                    {
                        D[i - 1] = D[i];
                    }

                    D[endC - 1] = E[j];
                }
            }

            // Print the contents of the LRU, LFU and OPT cache.
            printf("The Current Contents of the LRU Cache:\n");
            for (int i = 0; i < n; i++)
            {
                printf("%d ", A[i]);
            }
            printf("\n\n");
            
            printf("The Current Contents of the LFU Cache:\n");
            for (int i = 0; i < n; i++)
            {
                printf("%d ", B[i]);
            }
            printf("\n\n");

            printf("The Current Contents of the OPT Cache:\n");
            for (int i = 0; i < n; i++)
            {
                printf("%d ", D[i]);
            }
            printf("\n\n");
        }
        // Print the statistics.
        printf("Using %d frames, the reference string yielded:\n", n);
        printf("Scheme: LRU            #Faults: %d\n", faultsA);
        printf("Scheme: LFU            #Faults: %d\n", faultsB);
        printf("Scheme: OPT            #Faults: %d\n", faultsC);
    }
    return 0;
}
