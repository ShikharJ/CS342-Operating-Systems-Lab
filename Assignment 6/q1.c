#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

pthread_t *producers;								// Producer array.
pthread_t *consumers;								// Consumer array.
int sleep_time, producer_count, consumer_count;		// Command line arguments.
sem_t mutex, empty, full;							// Semaphores.

int buffer[25];										// Bounded buffer.
int buffer_position = -1;							// Buffer position.
int main_asleep = 1;								// Indicator of main()

// Function for indication of production.
int produce(pthread_t self)
{
	int i = 0;
	int p = 1 + (rand() % 40);
	while (!pthread_equal(producers[i], self) && i < producer_count)
	{
		i++;
	}
	printf("Producer %d Produced %d\n", i + 1, p);
	return p;
}

// Function for indication of consumption.
void consume(int p, pthread_t self)
{
	int i = 0;
	while (!pthread_equal(consumers[i], self) && i < consumer_count)
	{
		i++;
	}

	printf("\nBuffer: ");
	for (i = 0; i <= buffer_position; i++)
	{
		printf("%d ", buffer[i]);
	}
	printf("\nConsumer %d Consumed %d\nCurrent Buffer Length: %d\n", i + 1, p, buffer_position);
	
}

// Function for inserting an item into the buffer.
void insert_item(int p)
{
	buffer_position += 1;
	buffer[buffer_position] = p; 
}

// Function for removing an item from the buffer.
void remove_item(pthread_t self)
{
	char c = buffer[buffer_position];
	consume(c, self);
	buffer_position -= 1;
}

// Function for simulating the Producer thread.
void *producer(void *args)
{
	while (main_asleep)
	{
		int p = produce(pthread_self());
		sem_wait(&empty);
		sem_wait(&mutex);
		insert_item(p);
		sem_post(&mutex);
		sem_post(&full);
		sleep(1 + (rand() % 3));
	}	
	return NULL;
}

// Function for simulating the Consumer thread.
void *consumer(void *args)
{
	while (main_asleep)
	{
		sem_wait(&full);
		sem_wait(&mutex);
		remove_item(pthread_self());
		sem_post(&mutex);
		sem_post(&empty);
		sleep(1 + (rand() % 3));
	}
	return NULL;
}

int main(int argc, char **argv)
{
	if (argc != 4)				// Error checking.
	{
        printf("You Have Not Entered The Correct Number Of Arguments!\n");
        return 0;
    }

    sleep_time = atoi(argv[1]);				// Processing the arguments taken from command line.
    producer_count = atoi(argv[2]);
    consumer_count = atoi(argv[3]);

   	producers = (pthread_t *)malloc(producer_count * sizeof(pthread_t));	// Producer array.
   	consumers = (pthread_t *)malloc(consumer_count * sizeof(pthread_t));	// Consumer array.

	int i, error;
	srand(time(NULL));		// Initialize random seed.

	sem_init(&mutex, 0, 1);		// Initialize semaphores.
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, 25);

	// Create producer threads.
	for (i = 0; i < producer_count; i++)
	{
		error = pthread_create(&producers[i], NULL, &producer, NULL);
		if (error != 0)
		{
			fprintf(stderr, "Producer Thread Creation Failed!\n");
		}
	}

	// Create consumer threads.
	for (i = 0; i < consumer_count; i++)
	{
		error = pthread_create(&consumers[i], NULL, &consumer, NULL);
		if (error != 0)
		{
			fprintf(stderr, "Consumer Thread Creation Failed!\n");
		}
	}

	// Put the main() to sleep.
	sleep(sleep_time);
	// Indicate termination.
	main_asleep = 0;
	return 0;
}
