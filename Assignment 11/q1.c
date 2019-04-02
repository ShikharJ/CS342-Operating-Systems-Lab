#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// For storing the file description.
struct node{
    char name[20];
    int start_index;
    int end_index;
};

// For storing the available information regarding the files.
struct node table[20];
int memory[1000] = {};

int main()
{
    // Initialize the files.
    for (int i = 0; i < 20; i++)
    {
        table[i].start_index = -1;
        table[i].end_index = -1;
    }

    int exiter = 1;
    int n;
    char c;

    printf("Welcome To Sequential File Allocation!\n");
    while (exiter)
    {
        char s[20];
        printf("Enter The Command:\n");
        printf("1) Insert A New File\n");
        printf("2) Delete A File\n");
        printf("3) Print Table Contents\n");
        printf("4) Exit Program\n");
        printf("Enter Your Choice: ");
        scanf("%d%c", &n, &c);

        if (n == 1)
        {
            // Insert a new file into the disk.
            printf("Enter The File Name To Insert: ");
            scanf("%s", s);
            printf("Enter The File Size: ");
            scanf("%d%c", &n, &c);
            for (int i = 0; i < 20; i++)
            {
                int j;
                if (table[i].start_index == -1)
                {
                    for (j = 0; j < 1000;)
                    {
                        if (j + n - 1 < 1000)
                        {
                            int a = 0;
                            for (int k = j; k <= j + n; k++)
                            {
                                a |= memory[k];
                            }
                            if (a == 0){
                                for (int k = j; k < j + n; k++)
                                {
                                    memory[k] = 1;
                                }
                                strcpy(table[i].name, s);
                                table[i].start_index = j;
                                table[i].end_index = j + n - 1;
                                break;
                            } else
                            {
                                j += 1;
                                continue;
                            }
                        } else
                        {
                            j += n - 1;
                            break;
                        }
                    }

                    if (j < 1000)
                    {
                        break;
                    }
                }
                if (j >= 1000)
                {
                    printf("The Table Has Run Out Of Space!\n");
                }
            }
        } else if (n == 2)
        {
            // Delete a file by its name.
            printf("Enter The File Name To Delete: ");
            scanf("%s", s);
            for (int i = 0; i < 20; i++)
            {
                if (strcmp(s, table[i].name) == 0)
                {
                    for (int k = table[i].start_index; k <= table[i].end_index; k++)
                    {
                        memory[k] = 0;
                    }
                    table[i].start_index = -1;
                    table[i].end_index = -1;
                    strcpy(table[i].name, "");
                    break;
                } else
                {
                    printf("File Not Found!\n");
                }
            }
        } else if (n == 3)
        {
            // Print the contents of the allocation table.
            for (int i = 0; i < 20; i++)
            {
                if (table[i].start_index == -1)
                {
                    continue;
                } else
                {
                    printf("Name: %s\n", table[i].name);
                    printf("Start Index: %d\n", table[i].start_index);
                    printf("End Index: %d\n", table[i].end_index);
                }
            }
        } else if (n == 4)
        {
            printf("Thanks For Your Time!\n");
            break;
        } else
        {
            printf("Wrong Input Entered!\n");
        }
    }

    return 0;
}