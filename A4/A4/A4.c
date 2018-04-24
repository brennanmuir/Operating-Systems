// Brennan Muir
// CS4540 Spring 2018
// A4


// References
// https://github.com/jetsasank/operatingsystems/blob/master/buffer.c
// jetsasank provides a correct solution to the problem. I added some of my own work and formating to his solution as a reference
// www.codingalpha.com/producer-consumer-problem-c-program/
// This page from codingalpha also provided a correct solution, which I used as a reference
// https://www.geeksforgeeks.org/use-posix-semaphores-c/
// used this site to get a better understanding of semaphores

/*
In this project, you will design a programming solution to the bounded-buffer problem using the producer and consumer processes.
For this project, standard counting semaphores will be used for empty and full, and a mutex lock, rather than a binary semaphore, will be used to represent the pthread_mutex.
The producer and consumer (running as separate threads) will remove items to and from a buffer that is synchronized with these empty, full, and mutex structures.
*/

#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// The buffer.h file includes the code provided in the A4.pdf given out on elearning.

#define TRUE 1
// This was all included in figure 3 in the pdf
buffer_item buffer[BUFFER_SIZE];

pthread_mutex_t mutex;
sem_t empty;
sem_t full;

int insertPointer = 0, removePointer = 0;

void *producer(void *param);
void *consumer(void *param);

int insert_item(buffer_item item)
{
        int return_val = 0;
	sem_wait(&empty);

	pthread_mutex_lock(&mutex);
	if (insertPointer < BUFFER_SIZE) {
	buffer[insertPointer++] = item;
	insertPointer = insertPointer % 5;
	} else {
	    return_val = -1;
	}
	pthread_mutex_unlock(&mutex);
        sem_post(&full);

	return return_val;
}

int remove_item(buffer_item *item)
{
	int return_val;
	sem_wait(&full);

	pthread_mutex_lock(&mutex);
	if (insertPointer > 0) {
	*item = buffer[removePointer];
	buffer[removePointer++] = -1;
	removePointer = removePointer % 5;
    } else {
        return_val = -1;
    }
	pthread_mutex_unlock(&mutex);
	sem_post(&empty);

	return return_val;
}
// skeleton provided from figure 4 of pdf
int main(int argc, char *argv[]) {
  int i, j;

  // 1. Get command line arguments
  char* input1 = argv[1];
  char* input2 = argv[2];
  char* input3 = argv[3];

  int sleepTime = atoi(input1);
  int producerNum = atoi(input2);
  int consumerNum = atoi(input3);

  // Check that 4 parameters are passed
  if(argc != 4){
    printf("Need 4 parameters (./a.out <sleep> <numOfProducerThreads> <numOfConsumerThreads>)\n");
    exit(1);
  }

  // 2. Initialize buffer
  /* Initialize the synchronization tools */
  printf("\npthread mutex init: %d\n",pthread_mutex_init(&mutex, NULL));
  printf("sem empty: %d\n",sem_init(&empty, 0, 5));
  printf("sem full: %d\n",sem_init(&full, 0, 0));
  srand(time(0));

  // 3. Create the producer threads
  for(i = 0; i < producerNum; i++)
  {
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, producer, NULL);
  }

  // 4. Create the consumer threads
  for(j = 0; j < consumerNum; j++)
  {
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, consumer, NULL);
  }

  // 5. Sleep
  sleep(sleepTime);

  // 6. Exit
  return 0;

  }
  // Provided from figure 5
  void *producer(void *param)
  {
  buffer_item random;
  int r;

  while(TRUE)
  {
    r = rand() % 5;
    sleep(r);
    random = rand();

    if(insert_item(random))
      fprintf(stderr, "Error\n");

    printf("Producer produced: %d \n", random);

  }

  }
// Provided from figure 5
  void *consumer(void *param)
  {
  buffer_item random;
  int r;

  while(TRUE)
  {
    r = rand() % 5;
    sleep(r);

    if(remove_item(&random))
      fprintf(stderr, "Error Comsumer Remove_item waiting\n");
    else
      printf("Consumer consumed: %d \n", random);
  }
  }
