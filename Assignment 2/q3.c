#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int k = 5;

int main() 
{
	int pid, my_pid;
	pid = fork();

	if (pid == -1){
		fprintf(stderr, "Fork Failed!\n");
	} else if (pid == 0){
		my_pid = getpid();
		printf("Your are in child fork. PID: %d\n", my_pid);
		printf("Value of global variable in child: %d\n", k);
		k++;
		printf("Value of incremented global variable in child: %d\n", k);
		exit(0);
	} else {
		my_pid = getpid();
		printf("Your are in parent fork. PID: %d\n", my_pid);
		printf("Value of global variable in parent: %d\n", k);
		k--;
		printf("Value of decremented global variable in parent: %d\n", k);
		exit(0);
	}

	return 0; 
} 
