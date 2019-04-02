#include <stdio.h>
#include <math.h>

// Compile using * gcc q6.c -o q6 -lm *
int main()
{
	float t, m, h;
	char k;

    // Input the data.
    printf("Welcome To Effective Access Time Calculator!\n");
    printf("Enter The TLB Search Time (in ms): ");
    scanf("%f%c", &t, &k);
    printf("Enter The Memory Access Time (in ms): ");
    scanf("%f%c", &m, &k);
    printf("Enter The Hit Ratio: ");
    scanf("%f%c", &h, &k);

    // Calculate the effective access time.
    float a;
    a = ((m + t) * h) + (((2 * m) + t) * (1 - h));

    // Print the result.
    printf("Effective Memory Access Time: %f ms\n", a);
    return 0;
}