#include "Queue.h"

using namespace std;

void Queue::queue_initialize()
{
	q.head = NULL;
	q.tail = NULL;
	q.remaining_elements = 0;
}

void Queue::queue_add(int elem)
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

int Queue::queue_remove()
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

bool Queue::queue_full()
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
