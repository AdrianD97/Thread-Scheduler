#include "PriorityQueue.h"

PriorityQueue *createPriorityQueue(int size)
{
	return createEmptyHeap(size);
}

void add(PriorityQueue *priorityQueue, Node value)
{
	addItemToHeap(priorityQueue, value, MAX_HEAP);
}

Node const *head(const PriorityQueue *priorityQueue)
{
	return getHeapRoot(priorityQueue);
}

Node remove_head(PriorityQueue *priorityQueue)
{
	return removeHeapRoot(priorityQueue, MAX_HEAP);
}

void destroy(PriorityQueue *priorityQueue)
{
	freeHeapMemory(priorityQueue);
}
