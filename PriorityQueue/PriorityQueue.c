#include "PriorityQueue.h"

PriorityQueue* createPriorityQueue(int size)
{
	return createEmptyHeap(size);
}

void add(PriorityQueue *priorityQueue, Pair value)
{
	addItemToHeap(priorityQueue, value, MAX_HEAP);
}

Pair const* head(const PriorityQueue *priorityQueue)
{
	return getHeapRoot(priorityQueue);
}

Pair remove_head(PriorityQueue *priorityQueue)
{
	return removeHeapRoot(priorityQueue, MAX_HEAP);
}

void destroy(PriorityQueue *priorityQueue)
{
	freeHeapMemory(priorityQueue);
}
