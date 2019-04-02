#include <stdio.h>
#include <math.h>

// Compile using * gcc q5.c -o q5 -lm *
int main()
{
	int m, n, l, p;
	char k;

    // Input the data.
    printf("Welcome To Memory Calculator!\n");
    printf("Enter Virtual Address Space Size (in bits): ");
    scanf("%d%c", &m, &k);
    printf("Enter Page Size (in KB): ");
    scanf("%d%c", &n, &k);
    printf("Enter The Number Of Entries (in TLB): ");
    scanf("%d%c", &l, &k);
    printf("Enter The N-Way Associativeness: ");
    scanf("%d%c", &p, &k);

    // Calculate the answers to individual questions.
    float a, b;
    a = l / p;
    a = ceil(log2(a));
    b = floor(m - (log2((float)n) + 10));
    a = b - a;

    // Print the result.
    printf("Number Of Bits Needed For The TLB Tag: %d\n", (int)a);
    return 0;
}