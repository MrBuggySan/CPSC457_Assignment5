
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

#define NUM_PRODUCER 10
#define NUM_CONSUMER 1

struct thread_data
{
   int	thread_id;
   Queue* pQ;
   pthread_mutex_t* plock;
};

// CONSUMER routine
void *consumer(void *threadArgs){
	int msg_recieved_counter = 0;
  int prod_id = -1;
  int cons_id = cons_data->thread_id;
  struct thread_data *cons_data = (struct thread_data *)threadArgs;

	while(msg_recieved_counter <= 100){

		//try to lock
    pthread_mutex_lock(threadArgs->plock);

		//is the queue empty?
    if(!cons_data->pq->is_queue_empty){
      //not empty
			//get an element from the queue
      prod_id = cons_data->pq->queue_remove();
		    //was the queue full before?
					//yes - signal the producer
					// no - keep going
    }else{
      //empty - pthread_cond_wait

    }
    pthread_mutex_unlock(threadArgs->plock);


  	printf("Consumer thread #%d has recieved the message of %d\n", cons_id,  prod_id );

    //unlock
    printf("%d\n", msgOut);
    msg_recieved_counter++;
  }


  pthread_exit(NULL);
}

// PRODUCER routine
void *producer(void *threadArgs)
{
  int msg_sent_counter = 0;

	while(msg_sent_counter <= 10){
    //try to lock
    pthread_mutex_lock(threadArgs->plock);

  	//is the queue full?
  		//full- pthread_cond_wait

  		//not full
  			//add the id to the queue
  			//was it empty before?
  				//yes - signal the consumer
  				//no - keep going

  	//unlock
  }
	//test
	struct thread_data *prod_data = (struct thread_data *)threadArgs;
	printf("Producer thread #%d has recieved the arguments\n", prod_data->thread_id);
	pthread_exit(NULL);
}

// MAIN
int main()
{
	int rc=0;
	// pthread_cond_t notfull;
	// pthread_cond_t empty;

	pthread_t Producer_Threads[NUM_PRODUCER];
	pthread_t Consumer_Threads[NUM_CONSUMER];
	pthread_attr_t attr;
  pthread_mutex_t lock;
	/* Initialize and set thread detached attribute */
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


	pthread_mutex_init(&lock,NULL);

//Create the struct that contains Queue object and id
	struct thread_data producer_thread_data[NUM_PRODUCER];
	struct thread_data consumer_thread_data[NUM_CONSUMER];

//Create a single Queue object
	Queue* queue = new Queue();


  //Create the producer threads
	for(int i = 0; i < NUM_PRODUCER; i++){
		producer_thread_data[i].thread_id = i;
		producer_thread_data[i].pQ = queue;
    producer_thread_data[i].plock = &lock;
		// printf("Creating producer #%d \n", i);
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
		consumer_thread_data[i].pQ = queue;
    consumer_thread_data[i].plock = &lock;
		// printf("Creating consumer #%d \n", i);
		rc = pthread_create(&Consumer_Threads[i], &attr, consumer, (void *)
	       &consumer_thread_data[i]);
	  if (rc) {
	    printf("ERROR; return code from consumer pthread_create() is %d\n", rc);
	    exit(-1);
	    }
  }

  rc = 0;
	//Wait for all of the other threads to join
	pthread_attr_destroy(&attr);
  for(int t=0; t< NUM_PRODUCER + NUM_CONSUMER; t++) {
		if(t >= NUM_PRODUCER){
			rc = pthread_join(Consumer_Threads[t - NUM_PRODUCER], NULL);
      if (rc) {
         printf("Consumer thread #%d ERROR; return code from pthread_join() is %d\n", t,rc);
         exit(-1);
       }else{
         printf("Consumer thread #%d has exited succesfully\n",t);
       }
		}else{
			rc = pthread_join(Producer_Threads[t], NULL);
      if (rc) {
         printf("Producer thread #%d ERROR; return code from pthread_join() is %d\n", t,rc);
         exit(-1);
       }else{
         printf("Producer thread #%d has exited succesfully\n",t);
       }
		}


   }

	//delete pointers
	delete queue;
  pthread_mutex_destroy(&lock);

	printf("Main: program completed. Exiting.\n");
	// pthread_mutex_destroy(&mutex);
	pthread_exit(NULL);
}
