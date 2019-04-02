#include <stdio.h>
#include <math.h>

// Compile using * gcc q4.c -o q4 -lm *
int main()
{
	float m, l, p;
	char k;

	// Input the data.
    printf("Welcome To Memory Calculator!\n");
    printf("Enter Physical Address Space Size (in GB): ");
    scanf("%f%c", &m, &k);
    printf("Enter Virtual Address Space Size (in GB): ");
    scanf("%f%c", &l, &k);
    printf("Enter Page Size (in KB): ");
    scanf("%f%c", &p, &k);

    // Calculate the answers to individual questions.
    float a, b, c, d, e, f;
    a = l / p;
    b = m / p;
    c = log2(m) + 30;
    d = log2(l) + 30;
    e = log2(p) + 10;
    f = (log2(b) + 20) * a;

    // Print the answers.
    printf("Number Of Pages In The System: %lf * 2^{20}\n", a);
    printf("Number Of Frames In The System: %lf * 2^{20}\n", b);
    printf("Number Of Bits Required To Represent The Physical Address: %lf\n", c);
    printf("Number Of Bits Required To Represent The Virtual Address: %lf\n", d);
    printf("Number Of Bits Required To Represent The Page Offset: %lf\n", e);
    printf("Page Table Size: %lf * 2^{20} bits\n", f);
    return 0;
}