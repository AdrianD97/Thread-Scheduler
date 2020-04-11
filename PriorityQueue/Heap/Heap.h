#ifndef HEAP_H_
#define HEAP_H_

#include <stdlib.h>

#define MIN_HEAP 1
#define MAX_HEAP 0

#define ROOT 1

typedef struct {
	int size;
	int index;
	int (*compare)(void*, void*);
	void** arr;
} Heap;

typedef Heap MinHeap;
typedef Heap MaxHeap;

/* create an empty Heap (the method is a kind of C++ constructor) */
Heap* createEmptyHeap(int size, int (*compare)(void*, void*));

/*
	Add an item to Heap.
	type = MIN_HEAP -> heap is a min heap
	type = MAX_HEAP -> heap is a max heap
*/
void addItemToHeap(Heap* heap, void* value, int type);

/* get root of the heap */
void* getHeapRoot(const Heap* heap);

/*
	Remove and return root of the heap.
	type = MIN_HEAP -> heap is a min heap
	type = MAX_HEAP -> heap is a max heap
*/
void* removeHeapRoot(Heap* heap, int type);

/* free used memory */
void freeHeapMemory(Heap *heap);

#endif /* HEAP_H_ */
