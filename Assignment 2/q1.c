#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() 
{
	int child_pid, parent_pid;
	child_pid = fork(); 

	if (child_pid == -1){
		fprintf(stderr, "Fork Failed!\n");
	} else if (child_pid == 0){
		parent_pid = getppid();
		printf("Your are in child fork. Parent PID: %d\n", parent_pid);
		exit(0);
	} else {
		printf("Your are in parent fork. Child PID: %d\n", child_pid);
		exit(0);
	}

	return 0; 
} 