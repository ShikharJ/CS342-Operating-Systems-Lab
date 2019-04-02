#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// For storing the file description.
struct node
{
	struct node *next;
	int value;
};

// For storing the information regarding the file.
int num_blocks, file_count, current_block, current_size;
int disk[1000], temporary_free[1000];

// Function for checking the available space in the disk.
int check_disk()
{
	int j = 0, count = 1;
	temporary_free[0] = current_block;
	disk[current_block] = file_count + 1;
	for (int i = 1; i < current_size; i++)
	{
		while(j < num_blocks)
		{
			if(!disk[j])
			{
				temporary_free[i] = j;
				count += 1;
				j += 1;
				break;
			}
			j += 1;
		}
	}

	if (count == current_size) 
	{
		return 1;
	}

	disk[current_block] = 0;
	return 0;
}

int main()
{
	int choice;
	struct node *file_block[100];
	char file_name[1000][100], current_file[100];
	int indexed_block[1000], file_size[1000], deleted[1000];

	printf("Welcome To Linked File Allocation\n!");
	printf("Enter The Number Of Blocks In Disk: ");
	scanf("%d", &num_blocks);
	while (1)
	{
		printf("Enter The Command:\n");
		printf("1) Allocate Space To A New File\n");
		printf("2) Display Directory\n");
		printf("3) Exit\n");
		scanf("%d", &choice);
		if (choice == 1)
		{
			// Insert a new file into the disk.
			printf("Enter File Name: ");
			scanf("%s", current_file);
			printf("Enter Start Block Location And Length Of The File: ");
			scanf("%d %d", &current_block, &current_size);

			if (disk[current_block])
			{
				printf("\nError\n\n");
				continue;
			}
			if (check_disk())
			{
				file_count++;
				struct node *head = NULL;
				for (int i = 0; i < current_size; i++)
				{
					struct node *current = malloc(sizeof(struct node));
					current->value = temporary_free[i];
					current->next = NULL;
					if (head == NULL)
					{
						file_block[file_count] = current;
						head = current;
					} else
					{
						head->next = current;
						head = current;
					}
					disk[temporary_free[i]] = file_count;
				}
				strcpy(file_name[file_count], current_file);
				indexed_block[file_count] = current_block;
				file_size[file_count] = current_size;
			} else 
			{
				printf("\nError\n\n");
			}
		} else if (choice == 2)
		{
			// Print the contents of the allocation table.
			printf("\n%-20s%-20s%-20s%-20s\n", "File Name", "Indexed Block", "File Size", "Occupied Blocks");
			for (int i = 1; i <= file_count; i++)
			{
				if (!deleted[i])
				{
					printf("%-20s%-20d%-20d", file_name[i], indexed_block[i], file_size[i]);
					struct node *head = file_block[i];
					while (head != NULL)
					{
						printf("%d -> ", head->value);
						head = head->next;
					}
					printf("NULL\n");
				}
			}
			printf("\n") ;
		} else
		{
			printf("Thanks For Your Time!\n");
			break;
		}
	}
	return 0;
}