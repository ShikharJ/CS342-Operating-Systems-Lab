#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int factorial(int n){
	if (n == 1 || n == 0){
		return 1;
	}
	return n * factorial(n - 1);
}

int main() 
{
	int a = 5, b, c;
	int pid, my_pid;
	b = factorial(a);
	pid = fork(); 
	c = factorial(a);

	if (pid == -1){
		fprintf(stderr, "Fork Failed!\n");
	} else if (pid == 0){
		my_pid = getpid();
		printf("Your are in child fork. PID: %d\n", my_pid);
		printf("Value of factorial(5) in child before fork: %d\n", b);
		printf("Value of factorial(5) in child after fork: %d\n", c);
		exit(0);
	} else {
		my_pid = getpid();
		printf("Your are in parent fork. PID: %d\n", my_pid);
		printf("Value of factorial(5) in parent before fork: %d\n", b);
		printf("Value of factorial(5) in parent after fork: %d\n", c);
		exit(0);
	}

	return 0; 
} 
