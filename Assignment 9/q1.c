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

        // Create and initialize OPT buffers.
        int A[n];
        int B[1000];
        for (int i = 0; i < n; i++)
        {
            A[i] = 0;
        }

        int element, end = 0, faults = 0;
        int k = 0;
        // Input the elements.
        while (fscanf(fp, "%d", &element) > 0)
        {
            B[k] = element;
            k++;
            if (element == -1)
            {
                k--;
                break;
            }
        }

        for (int j = 0; j < k; j++)
        {
            printf("The Element Entered: %d\n", B[j]);
            int found = -1;

            for (int i = 0; i < n; i++)
            {
                // Search the element in OPT cache.
                if (A[i] == B[j])
                {
                    found = 1; 
                    break;
                } else
                {
                    continue;
                }
            }

            if (found == -1)
            {
                // Enter the element into the OPT cache in case page fault occurs.
                printf("Fault Occurred in OPT cache! \n");
                faults += 1;
                if (end < n)
                {
                    A[end] = B[j];
                    end++;
                } else
                {
                    int max = -1;
                    int index = -1;
                    
                    for (int i = 0; i < n; i++)
                    {
                        int local_max = -1;
                        for (int l = j + 1; l < k; l++)
                        {
                            if (B[l] == A[i])
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
                        A[i - 1] = A[i];
                    }

                    A[end - 1] = B[j];
                }
            }

            // Print the contents of the OPT cache.
            printf("The Current Contents of the OPT Cache:\n");
            for (int i = 0; i < n; i++)
            {
                printf("%d ", A[i]);
            }
            printf("\n\n");
        }
        // Print the statistics.
        printf("Using %d frames, the reference string yielded:\n", n);
        printf("Scheme: OPT            #Faults: %d\n", faults);
    }
    return 0;
}