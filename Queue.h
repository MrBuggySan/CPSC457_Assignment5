#ifndef QUEUE_H
#define QUEUE_H

#define MAX_QUEUE_SIZE 20

typedef char uint8_t;

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
    bool queue_full();
    bool is_queue_empty();
};


#endif
