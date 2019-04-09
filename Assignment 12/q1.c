#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>

// Declare the file pointer, semaphores, and local variables.
FILE *fp;
sem_t mutex, writeblock;
int rcount = 0, maximum = 10, looper = 1, count;

// Function to simulate the reader process.
void *reader()
{
	pthread_t f = pthread_self();
  	while (looper == 1)
  	{
  		sem_wait(&mutex);
  		printf("Reader(%ld) Enters.\n", f);
  		rcount = rcount + 1;
  		if (rcount == 1)
  		{
  			// Acquire the file lock or wait for writer to finish writing.
   			sem_wait(&writeblock);
   			fp = fopen("buffer.txt", "r");
		}
  		sem_post(&mutex);
  		fscanf(fp, "%d", &count);
  		printf("Reader(%ld) Reads Value: %d\n", f, count);
  		sleep(1);
  		sem_wait(&mutex);
  		printf("Reader(%ld) Leaves.\n", f);
  		rcount = rcount - 1;
  		if (rcount == 0)
  		{
  			fclose(fp);
  			// Release the file lock back to the writer.
   			sem_post(&writeblock);
  		}
  		sem_post(&mutex);
  		sleep(1 + (rand() % 3));
  	}
}

// Function to simulate the writer process.
void *writer()
{
	pthread_t f = pthread_self();
	while (looper == 1)
	{
		// Acquire the file lock for writing.
  		sem_wait(&writeblock);
  		printf("Writer(%ld) Enters.\n", f);
  		fp = fopen("buffer.txt", "w+");
  		fscanf(fp, "%d", &count);
  		count++;
  		printf("Writer(%ld) Writes The Value: %d\n", f, count);
  		fprintf(fp, "%d", count);
  		fclose(fp);
  		sleep(1);
  		if (count >= maximum)
  		{
  			looper = 0;
  		}
  		printf("Writer(%ld) Leaves.\n", f);
  		// Release the file lock.
  		sem_post(&writeblock);
  		sleep(1 + (rand() % 3));
  	}
}

int main() 
{
	// Initialize the semaphores.
	pthread_t rtid[2], wtid;
	sem_init(&mutex, 0, 1);
  	sem_init(&writeblock, 0, 1);

  	// Set the random seed value and initialize the buffer file.
  	srand(time(NULL));
	fp = fopen("buffer.txt", "w");
	fprintf(fp, "%d", 0);
	fclose(fp);
	printf("File Created.\nVariable Is Set To 0.\n");

	// Create the reader and writer processes.
	pthread_create(&rtid[0], NULL, reader, NULL);
	pthread_create(&rtid[1], NULL, reader, NULL);
	pthread_create(&wtid, NULL, writer, NULL);

	// Join the threads on termination.
    pthread_join(wtid, NULL);
    pthread_join(rtid[0], NULL);
    pthread_join(rtid[1], NULL);

	return 0;
}