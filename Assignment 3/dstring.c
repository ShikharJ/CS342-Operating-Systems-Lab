#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

//Please compile as gcc -o dstring dstring.c
int main(int argc, char *argv[])
{
    if (argc < 1){					//Error checking
        printf("You have not entered the required number of arguments!\n");
        return 0;
    }

    FILE *fp = fopen(argv[1], "r");			//File open
    char word[100];
    int count = 0;
    printf("The words (at multiple positions of 3) are: \n");

    while(fscanf(fp, "%s", word) > 0)		//Word read at multiple of 3
    {
    	count += 1;
    	if (count % 3 == 0)
    	{
    		printf("%s\n", word);			//Print the words
    	}
    }
    printf("\n");
    fclose(fp);								//Close the file

    return 0;
}