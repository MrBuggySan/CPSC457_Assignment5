#ifndef QUEUE_H
#define QUEUE_H

#define MAX_QUEUE_SIZE 20
#include <stdint.h>

//typedef char uint8_t;

class Queue{
  private:
    // QUEUE
    struct queue{
    	int element[MAX_QUEUE_SIZE];
    	uint8_t head;
    	uint8_t tail;
    	uint8_t remaining_elements;
    } q;

  public:


    void queue_initialize();
    void queue_add(int elem);
    int queue_remove();
    bool is_queue_full();
    bool is_queue_empty();
};

using namespace std;

void Queue::queue_initialize(){
	q.head = -1;
	q.tail = -1;
	q.remaining_elements = 0;
}

void Queue::queue_add(int elem){
	//check if queue is full
	if(is_queue_full()){
		return;
	}

	if(q.head == -1 || q.tail == -1){
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
		q.head = -1;
		q.tail = -1;
	}
	
	if(q.head == MAX_QUEUE_SIZE){
		q.head = 0;
	}
	return prodMsg;
}

bool Queue::is_queue_full(){
	if(q.remaining_elements >= MAX_QUEUE_SIZE){
		return true;
	}
	else{
		return false;
	}
}

bool Queue::is_queue_empty(){
  return (q.remaining_elements == 0)? true: false;
}



#endif
