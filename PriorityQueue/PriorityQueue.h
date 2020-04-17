#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

#include "Heap/Heap.h"

typedef MaxHeap PriorityQueue;

/* create an empty Priority Queue (the method is a kind of C++ constructor) */
PriorityQueue *createPriorityQueue(int size);

/* add an item to Priority Queue */
void add(PriorityQueue *priorityQueue, Node value);

/* get head of the Priority Queue */
Node const *head(const PriorityQueue *priorityQueue);

/* remove head of the Priority Queue */
Node remove_head(PriorityQueue *priorityQueue);

/* free used memory */
void destroy(PriorityQueue *priorityQueue);

#endif /* PRIORITY_QUEUE_H_ */
