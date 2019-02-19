#include <stdio.h>
#include <stdlib.h>

/* Uninitialized global variables stored in BSS */
int uninitialized_global1;
int uninitialized_global2;
/* Initialized global variable stored in Data Segment */
int initialized_global = 10;

int main(void)
{
	/* Initialized static variable stored in Data Segment */
    static int i = 100;
    /* Initialized variables stored in Stack */
    int j = 10;
    int k = 10;
    /* Initialized memory chunk stored in Heap */
    int *p = (int *) malloc(2 * sizeof(int));

    // Print the addresses of the elements stored in each of the segments.
    printf("The BSS Segment Begins At: %p\n", &uninitialized_global2);
    printf("The BSS Segment Ends At: %p\n", &uninitialized_global1);
    printf("The Data Segment Begins At: %p\n", &initialized_global);
    printf("The Data Segment Ends At: %p\n", &i);
    printf("The Stack Segment Begins At: %p\n", &j);
    printf("The Stack Segment Ends At: %p\n", &k);
    printf("The Heap Segment Begins At: %p\n", p);
    printf("The Heap Segment Ends At: %p\n", p + 4);
    printf("The Text Segment Is At: %p\n", main);

    // Test the readability and writability of the different segments.
    int *q = NULL;
    printf("Testing Readability and Writability of BSS\n");
    q = &uninitialized_global2;
    printf("The BSS Segment Read and Write Test:\n");
    printf("Read Value at %p: %d\n", &uninitialized_global2, *q);
    printf("Writing Value at %p: %d\n", &uninitialized_global2, 15);
    *q = 15;
    printf("Final Value at %p: %d\n", &uninitialized_global2, *q);

    q = &initialized_global;
    printf("The Data Segment Read and Write Test:\n");
    printf("Read Value at %p: %d\n", &initialized_global, *q);
    printf("Writing Value at %p: %d\n", &initialized_global, 15);
    *q = 15;
    printf("Final Value at %p: %d\n", &initialized_global, *q);

    q = &j;
    printf("The Stack Segment Read and Write Test:\n");
    printf("Read Value at %p: %d\n", &j, *q);
    printf("Writing Value at %p: %d\n", &j, 15);
    *q = 15;
    printf("Final Value at %p: %d\n", &j, *q);

    q = p;
    printf("The Heap Segment Read and Write Test:\n");
    printf("Read Value at %p: %d\n", p, *q);
    printf("Writing Value at %p: %d\n", p, 15);
    *q = 15;
    printf("Final Value at %p: %d\n", p, *q);

    q = (int *)main;
    printf("The Text Segment Read and Write Test:\n");
    printf("Read Value at %p: %d\n", main, *q);
    printf("Writing Value To Text Segment Leads To Core Dump!!\n");

    return 0;
}