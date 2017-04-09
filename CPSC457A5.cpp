
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

#define NUM_PRODUCER 10
#define NUM_CONSUMER 1

struct thread_data
{
   int	thread_id;
   Queue* q;
};

// CONSUMER routine
void *consumer(void *threadArgs){
	//cache the queue object


	//
	// int msgCount = 0;
	// int msgOut;
	// while(msgCount < 100)
	// {
	//
	// 	//try to lock
	//
	// 	//is the queue empty?
	// 		//empty - pthread_cond_wait
	// 		//not empty
	// 			//get an element from the queue
	// 			//was the queue full before?
	// 				//yes - signal the producer
	// 				// no - keep going
	//
	// 	//unlock
	//
	//
	// 	if(q.remaining_elements <= 0)
	// 	{
	// 		while(!empty)
	// 		{
	// 			pthread_cond_wait(&empty);
	// 		}
	// 	}
	// 	msgOut = queue_remove(q);
	// 	printf("%d\n", msgOut);
	// 	msgCount++;
	// }

	//test
	struct thread_data *cons_data = (struct thread_data *)threadArgs;
	printf("Consumer thread #%d has recieved the arguments", cons_data->thread_id);
	pthread_exit(NULL);
}

// PRODUCER routine
void *producer(void *threadArgs)
{
	// int tid;
	// tid = (int)threadId;

	//cache the queue object


	//try to lock

	//is the queue full?
		//full- pthread_cond_wait

		//not full
			//add the id to the queue
			//was it empty before?
				//yes - signal the consumer
				//no - keep going

	//unlock


	//test
	struct thread_data *prod_data = (struct thread_data *)threadArgs;
	printf("Producer thread #%d has recieved the arguments", prod_data->thread_id);
	pthread_exit(NULL);
}

// MAIN
int main()
{
	int rc;
	// pthread_mutex_t lock;

	//?
	// pthread_cond_t notfull;
	// pthread_cond_t empty;

	pthread_t Producer_Threads[NUM_PRODUCER];
	pthread_t Consumer_Threads[NUM_CONSUMER];
	pthread_attr_t attr;
	/* Initialize and set thread detached attribute */
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


	// pthread_mutex_init(&lock,NULL);

//Create the struct that contains Queue object and id
	struct thread_data producer_thread_data[NUM_PRODUCER];
	struct thread_data consumer_thread_data[NUM_CONSUMER];

//Create a single Queue object
	Queue* queue = new Queue();


  //Create the producer threads
	for(int i = 0; i < NUM_PRODUCER; i++){
		producer_thread_data[i].thread_id = i;
		producer_thread_data[i].q = queue;
		printf("Creating producer #%d \n", i);
		rc = pthread_create(&Producer_Threads[i], &attr, producer, (void *)
	       &producer_thread_data[i]);
	  if (rc) {
	    printf("ERROR; return code from producer pthread_create() is %d\n", rc);
	    exit(-1);
	    }
  }


  //Create the consumer threads
	for(int i = 0; i < NUM_CONSUMER; i++){
		consumer_thread_data[i].thread_id = i;
		consumer_thread_data[i].q = queue;
		printf("Creating consumer #%d \n", i);
		rc = pthread_create(&Consumer_Threads[i], &attr, consumer, (void *)
	       &consumer_thread_data[i]);
	  if (rc) {
	    printf("ERROR; return code from consumer pthread_create() is %d\n", rc);
	    exit(-1);
	    }
  }


	//Wait for all of the other threads to join
	pthread_attr_destroy(&attr);
  for(int t=0; t< NUM_PRODUCER + NUM_CONSUMER; t++) {
		if(t >= NUM_PRODUCER){
			rc = pthread_join(Consumer_Threads[t], NULL);
		}else{
			rc = pthread_join(Producer_Threads[t], NULL);
		}
     if (rc) {
        printf("ERROR; return code from pthread_join() is %d\n", rc);
        exit(-1);
        }

   }

	//delete pointers
	delete queue;

	printf("Main: program completed. Exiting.\n");
	// pthread_mutex_destroy(&mutex);
	pthread_exit(NULL);
}
