
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
   pthread_cond_t* pcond;
   bool* prod_waiting;
};

// CONSUMER routine
void *consumer(void *threadArgs){
	int msg_recieved_counter = 0;
  int prod_id = -1;
  
  struct thread_data *cons_data = (struct thread_data *)threadArgs;
	int cons_id = cons_data->thread_id;
	while(msg_recieved_counter <= 100){

		//try to lock
    pthread_mutex_lock(cons_data->plock);

		//is the queue empty?
    if(cons_data->pQ->is_queue_empty()){
      //empty - pthread_cond_wait
      pthread_cond_wait(cons_data->pcond, cons_data->plock);
    }
    //not empty

    //check if queue was full
    bool wasFull = cons_data->pQ->is_queue_full();

    //get an element from the queue
    prod_id = cons_data->pQ->queue_remove();
    msg_recieved_counter++;
    printf("Consumer thread #%d has recieved the message of %d\n", cons_id,  prod_id );

    //was the queue full before?
    if(wasFull){
        //yes - signal the producer
        pthread_cond_signal(cons_data->pcond);
    }
    // no - keep going


    //unlock
    pthread_mutex_unlock(cons_data->plock);



  }


  pthread_exit(NULL);
}

// PRODUCER routine
void *producer(void *threadArgs)
{
  struct thread_data *prod_data = (struct thread_data *)threadArgs;
  int msg_sent_counter = 0;

	while(msg_sent_counter <= 10){
    //try to lock
    pthread_mutex_lock(prod_data->plock);

    //check if a producer is waiting
    if(*(prod_data->prod_waiting)){
      //is the queue full?
      if(prod_data->pQ->is_queue_full()){
        //full- pthread_cond_wait
        *(prod_data->prod_waiting) = true;
        pthread_cond_wait(prod_data->pcond, prod_data->plock);
        *(prod_data->prod_waiting) = false;
      }
      //not full

      //check if queue was empty
      bool wasEmpty = prod_data->pQ->is_queue_empty();

      //add the id to the queue
      prod_data->pQ->queue_add(prod_data->thread_id);
      msg_sent_counter++;
      printf("Producer #%d thread has written the message to the queue\n", prod_data->thread_id);

      //was it empty before?
      if(wasEmpty){
        //yes - signal the consumer
        pthread_cond_signal(prod_data->pcond);
      }
    }
  	//unlock
    pthread_mutex_unlock(prod_data->plock);
  }

	pthread_exit(NULL);
}

// MAIN
int main()
{
	int rc=0;


  pthread_cond_t thread_cond;

  pthread_cond_init (&thread_cond, NULL);

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
  queue->queue_initialize();

  bool *wait_flag = new bool;
  *wait_flag = false;
  //Create the producer threads
	for(int i = 0; i < NUM_PRODUCER; i++){
		producer_thread_data[i].thread_id = i;
		producer_thread_data[i].pQ = queue;
    producer_thread_data[i].plock = &lock;
    producer_thread_data[i].pcond = &thread_cond;
    producer_thread_data[i].prod_waiting = wait_flag;
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
    consumer_thread_data[i].pcond = &thread_cond;
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
  pthread_cond_destroy(&thread_cond);

	printf("Main: program completed. Exiting.\n");
	// pthread_mutex_destroy(&mutex);
	pthread_exit(NULL);
}
