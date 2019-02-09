#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc <= 1){
		printf("You have not entered the required number of arguments!\n");
		return 0;
	}
	int i, t = atoi(argv[1]);
	int pid, my_pid;
	pid = fork();

	if (pid == -1){
		fprintf(stderr, "Fork Failed!\n");
	} else if (pid == 0){
		my_pid = getpid();
		printf("Your are in child fork. PID: %d\n", my_pid);
		printf("Putting to sleep for %d seconds!\n", t);
		for (i = 0; i < t; i++){
			sleep(1);
			printf(".\n");
		}
		printf("List of processes running from child:\n");
		system("ps");
		exit(0);
	} else {
		my_pid = getpid();
		printf("Your are in parent fork. PID: %d\n", my_pid);
		printf("The parent is waiting for the child to terminate.\n");
		wait(NULL);
		printf("The child has terminated.\n");
		printf("List of processes running from parent:\n");
		system("ps");
		printf("The parent will exit now.\n");
		exit(0);
	}

	return 0; 
} 
