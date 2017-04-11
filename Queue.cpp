#include "Queue.h"

using namespace std;

void Queue::queue_initialize(){
	q.head = NULL;
	q.tail = NULL;
	q.remaining_elements = 0;
}

void Queue::queue_add(int elem){
	//check if queue is full
	if(is_queue_full()){
		return;
	}

	if(head == NULL || tail == NULL){
		q.head = 0;
		q.tail = 0;
	}
	q.element[q.tail++] = elem;
	q.remaining_elements++;
	if(q.tail == MAX_QUEUE_SIZE){
		q.tail = 0;
	}
}

int Queue::queue_remove(){
	//check if queue is empty
	if(is_queue_empty()){
		return -1;
	}

	int prodMsg;
	prodMsg = q.element[q.head++];
	q.remaining_elements--;
	if(q.remaining_elements == 0){
		q.head = NULL;
		q.tail = NULL;
	}
	
	if(q.head == MAX_QUEUE_SIZE){
		q.head = 0;
	}
	return prodMsg;
}

bool Queue::is_queue_full(){
	if(remaining_elements >= MAX_QUEUE_SIZE){
		return true;
	}
	else{
		return false;
	}
}

bool Queue::is_queue_empty(){
  return (remaining_elements == 0)? true: false;
}
