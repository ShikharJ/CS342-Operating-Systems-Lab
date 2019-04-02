#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// For storing the information regarding the file.
int num_blocks, file_count, current_block, current_size;
int disk[1000], temporary_free[1000];

// Function for checking the available space in the disk.
int check_disk()
{
	int j = 0, count = 0;
	disk[current_block] = file_count + 1;
	for (int i = 0; i < current_size; i++)
		while (j < num_blocks)
		{
			if (!disk[j])
			{
				temporary_free[i] = j;
				count++;
				j++;
				break;
			}
			j++;
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
	char file_name[1000][100], current_file[100];
	int indexed_block[1000], file_size[1000], file_block[1000][1000];
	printf("Welcome To Indexed File Allocation!\n");
	printf("Enter Number Of Blocks In Disk: ");
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
			printf("Enter Indexed Block Location And Length Of The File (Separated By A Space): ");
			scanf("%d %d", &current_block, &current_size);

			if (disk[current_block])
			{
				printf("Error!\n") ;
				continue;
			}

			if (check_disk())
			{
				file_count++;
				for (int i = 0; i < current_size; i++)
				{
					disk[temporary_free[i]] = file_count;
					file_block[file_count][i] = temporary_free[i];
				}
				strcpy(file_name[file_count], current_file);
				indexed_block[file_count] = current_block;
				file_size[file_count] = current_size;
			} else
			{
				printf("Error!\n");
			}
		} else if (choice == 2)
		{
			// Print the contents of the allocation table.
			printf("%-20s%-20s%-20s%-20s\n", "File Name", "Indexed Block", "File Size", "Occupied Blocks");

			for (int i = 1; i <= file_count; i++)
			{
				printf("%-20s%-20d%-20d", file_name[i], indexed_block[i], file_size[i]);

				for (int j = 0; j < file_size[i]; j++)
				{
					printf("%d ", file_block[i][j]);
				}
				printf("\n");
			}
		} else
		{
			printf("Thanks For Your Time!\n");
			break;
		}
	}
	return 0;
}