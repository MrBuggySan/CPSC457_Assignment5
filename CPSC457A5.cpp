
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 20
// QUEUE
typedef struct queue{
	int element[MAX_QUEUE_SIZE];
	uint8_t head;
	uint8_t tail;
	uint8_t remaining_elements;
} prod_cons_queue;

pthread_mutex_t lock;
pthread_cond_t notfull;
pthread_cond_t empty;

void queue_initialize(prod_cons_queue *q)
{
	q.head = NULL;
	q.tail = NULL;
	q.remaining_elements = 0;
}

void queue_add(prod_cons_queue *q, int elem)
{
	while(queue_full(q))
	{
		while(!notfull)
		{
			pthread_cond_wait(&notfull, &mutex);
		}
		pthread_mutex_lock(&lock);
		if(queue_full(q))
		{
			pthread_mutex_unlock(&lock);
		}
	}
	if(head == NULL || tail == NULL)
	{
		q.head = 0;
		q.tail = 0;
		pthread_cond_signal(&empty);
	}
	q.tail++;
	if(q.tail >= MAX_QUEUE_SIZE)
	{
		q.tail = 0;
	}
	q.element[q.tail] = elem;
	q.remaining_elements++;
	pthread_mutex_unlock(&lock);
}

int queue_remove(prod_cons_queue *q)
{
	pthread_mutex_lock(&lock);
	int prodMsg;
	prodMsg = q.element[q.head];
	q.remaining_elements--;
	q.head++;
	if(q.head >= MAX_QUEUE_SIZE)
	{
		q.head = 0;
	}
	if(q.remaining_elements <= 0)
	{
		q.head = NULL;
		q.tail = NULL;
	}
	pthread_mutex_unlock(&lock);
	return prodMsg;
}

boolean queue_full(prod_cons_queue *q)
{
	if(remaining_elements >= MAX_QUEUE_SIZE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// CONSUMER
void *consumer(void *q){
	int msgCount = 0;
	int msgOut;
	while(msgCount < 100)
	{
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

// PRODUCER
void *producer(void *threadId)
{
	int tid;
	tid = (int)threadId;
}

// MAIN
int main()
{
	pthread_mutex_init(&lock,NULL);

	pthread_mutex_destroy(&mutex);
}
