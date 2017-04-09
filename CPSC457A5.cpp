
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
void *consumer(void *q){
	//cache the queue object



	int msgCount = 0;
	int msgOut;
	while(msgCount < 100)
	{

		//try to lock

		//is the queue empty?
			//empty - pthread_cond_wait
			//not empty
				//get an element from the queue
				//was the queue full before?
					//yes - signal the producer
					// no - keep going

		//unlock


		if(q.remaining_elements <= 0)
		{
			while(!empty)
			{
				pthread_cond_wait(&empty);
			}
		}
		msgOut = queue_remove(q);
		printf("%d\n", msgOut);
		msgCount++;
	}
	pthread_exit(NULL);
}

// PRODUCER routine
void *producer(void *threadId)
{
	int tid;
	tid = (int)threadId;

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

}

// MAIN
int main()
{
	int rc;
	pthread_mutex_t lock;

	//?
	pthread_cond_t notfull;
	pthread_cond_t empty;

	pthread_t Producer_Threads[NUM_PRODUCER];
	pthread_t Consumer;

	pthread_mutex_init(&lock,NULL);

//Create the struct that contains Queue object and id
	struct thread_data thread_data_array[NUM_PRODUCER + NUM_CONSUMER];

//Create a single Queue object
	Queue* queue = new Queue();


//Create the producer threads
	for(int i = 0; i < NUM_PRODUCER; i++){
		thread_data_array[i].thread_id = t;
		thread_data_array[i].q = queue;
		printf("Creating producer #%d \n", i);
		rc = pthread_create(&Producer_Threads[t], NULL, producer, (void *)
	       &thread_data_array[t]);
	  if (rc) {
	    printf("ERROR; return code from producer pthread_create() is %d\n", rc);
	    exit(-1);
	    }
	  }
	}

//Create the consumer threads
	int consum_start_index = NUM_PRODUCER;
	int consum_end_index = NUM_PRODUCER + NUM_CONSUMER;
	for(int i = consum_start_index; i < consum_end_index; i++){
		thread_data_array[i].thread_id = t;
		thread_data_array[i].q = queue;
		printf("Creating consumer #%d \n", i);
		rc = pthread_create(&Producer_Threads[t], NULL, producer, (void *)
	       &thread_data_array[t]);
	  if (rc) {
	    printf("ERROR; return code from consumer pthread_create() is %d\n", rc);
	    exit(-1);
	    }
	  }

	}




	//Wait for all of the other threads to join

	//delete pointers
	delete queue;

	pthread_mutex_destroy(&mutex);
}
