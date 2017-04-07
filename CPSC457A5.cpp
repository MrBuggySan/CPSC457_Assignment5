
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


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

	pthread_mutex_t lock;
	pthread_cond_t notfull;
	pthread_cond_t empty;

	pthread_t Producer_Threads[10];
	pthread_t Consumer;


//Create the Queue object

//Create the threads and pass the Queue object and id to them

	pthread_mutex_init(&lock,NULL);



	pthread_mutex_destroy(&mutex);
}
