#ifndef QUEUE_H
#define QUEUE_H

/**
    @brief A data structure representing a queue.
 */
typedef struct
{
    int front;
    int rear;
    int capacity;
    int size;
    int **queue; // Array of pointers pointing at the queue's items
} Queue;

/**
    @brief Initialize the queue with specified capacity
    @param queue Pointer to the pointer of the queue so it modifies the queue itself
    @param capacity Queue's max capacity
*/
void initQueue(Queue **queue, int capacity);

/**
    @brief Add new item to the rear of queue
    @param queue Pointer to queue
    @param newItem Item to be added to the rear of the queue
*/
void enqueue(Queue *queue, int newItem);

/**
    @brief Remove the head of the queue and return it
    @param queue Pointer to queue
    @return Queue's removed head
*/
int dequeue(Queue *queue);

int getHead(Queue *queue);
int getRear(Queue *queue);
int isEmpty(Queue *queue);
int isFull(Queue *queue);
void free(Queue *queue);

#endif