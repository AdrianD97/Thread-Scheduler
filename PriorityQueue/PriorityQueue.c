#include "PriorityQueue.h"

PriorityQueue* createPriorityQueue(int size, int (*compare)(void*, void*))
{
	return createEmptyHeap(size, compare);
}

void add(PriorityQueue *priorityQueue, void* value)
{
	addItemToHeap(priorityQueue, value, MAX_HEAP);
}

void* head(const PriorityQueue *priorityQueue)
{
	return getHeapRoot(priorityQueue);
}

void* remove_head(PriorityQueue *priorityQueue)
{
	return removeHeapRoot(priorityQueue, MAX_HEAP);
}

void destroy(PriorityQueue *priorityQueue)
{
	freeHeapMemory(priorityQueue);
}
