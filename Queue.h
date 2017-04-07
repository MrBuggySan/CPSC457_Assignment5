#ifndef QUEUE_H
#define QUEUE_H

#define MAX_QUEUE_SIZE 20

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
    Queue();

    queue_initialize();
    queue_add(int elem);
    queue_remove();
    queue_full();
}


#endif
