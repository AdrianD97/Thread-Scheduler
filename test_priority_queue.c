#include <stdio.h>
#include <assert.h>

#include "utils/utils.h"
#include "PriorityQueue/PriorityQueue.h"
/* TODO: SA rertestez acum, pentru ca am schimbat in structura de date */

void test_priority_queue()
{
	printf("Start test.\n");

	Pair pair1, pair2, pair3, pair4, pair5, pair6, pair7;

	pair1.index = 0;
	pair1.priority = 3;

	pair2.index = 1;
	pair2.priority = 2;

	pair3.index = 2;
	pair3.priority = 5;

	pair4.index = 3;
	pair4.priority = 3;

	pair5.index = 4;
	pair5.priority = 8;

	pair6.index = 5;
	pair6.priority = 0;

	pair7.index = 6;
	pair7.priority = 8;

	void *head_;
	PriorityQueue *priorityQueue;
	int size = 10;

	priorityQueue = createPriorityQueue(size, compare_pairs);
	assert(priorityQueue != NULL);
	assert(priorityQueue->size == size);
	assert(priorityQueue->index == 0);
	assert(priorityQueue->compare == compare_pairs);
	assert(priorityQueue->arr != NULL);
	assert(priorityQueue->arr[1] == 0);
	assert(priorityQueue->arr[size] == 0);

	add(priorityQueue, (void *)&pair1);
	assert(priorityQueue->index == 1);
	assert((*(Pair *)priorityQueue->arr[1]).priority == pair1.priority);
	assert((*(Pair *)priorityQueue->arr[1]).index == pair1.index);

	head_ = head(priorityQueue);
	assert(head_ != NULL);
	assert((*(Pair *)head_).priority == pair1.priority);
	assert((*(Pair *)head_).index == pair1.index);

	add(priorityQueue, (void *)&pair2);
	assert(priorityQueue->index == 2);
	assert((*(Pair *)priorityQueue->arr[1]).priority == pair1.priority);
	assert((*(Pair *)priorityQueue->arr[1]).index == pair1.index);
	assert((*(Pair *)priorityQueue->arr[2]).priority == pair2.priority);
	assert((*(Pair *)priorityQueue->arr[2]).index == pair2.index);

	head_ = head(priorityQueue);
	assert(head_ != NULL);
	assert((*(Pair *)head_).priority == pair1.priority);
	assert((*(Pair *)head_).index == pair1.index);

	add(priorityQueue, (void *)&pair3);
	assert(priorityQueue->index == 3);
	assert((*(Pair *)priorityQueue->arr[1]).priority == pair3.priority);
	assert((*(Pair *)priorityQueue->arr[1]).index == pair3.index);
	assert((*(Pair *)priorityQueue->arr[2]).priority == pair2.priority);
	assert((*(Pair *)priorityQueue->arr[2]).index == pair2.index);
	assert((*(Pair *)priorityQueue->arr[3]).priority == pair1.priority);
	assert((*(Pair *)priorityQueue->arr[3]).index == pair1.index);

	head_ = head(priorityQueue);
	assert(head_ != NULL);
	assert((*(Pair *)head_).priority == pair3.priority);
	assert((*(Pair *)head_).index == pair3.index);
	
	add(priorityQueue, (void *)&pair4);
	assert(priorityQueue->index == 4);
	assert((*(Pair *)priorityQueue->arr[1]).priority == pair3.priority);
	assert((*(Pair *)priorityQueue->arr[1]).index == pair3.index);
	assert((*(Pair *)priorityQueue->arr[2]).priority == pair4.priority);
	assert((*(Pair *)priorityQueue->arr[2]).index == pair4.index);
	assert((*(Pair *)priorityQueue->arr[3]).priority == pair1.priority);
	assert((*(Pair *)priorityQueue->arr[3]).index == pair1.index);
	assert((*(Pair *)priorityQueue->arr[4]).priority == pair2.priority);
	assert((*(Pair *)priorityQueue->arr[4]).index == pair2.index);

	head_ = head(priorityQueue);
	assert(head_ != NULL);
	assert((*(Pair *)head_).priority == pair3.priority);
	assert((*(Pair *)head_).index == pair3.index);
	
	add(priorityQueue, (void *)&pair5);
	assert(priorityQueue->index == 5);
	assert((*(Pair *)priorityQueue->arr[1]).priority == pair5.priority);
	assert((*(Pair *)priorityQueue->arr[1]).index == pair5.index);
	assert((*(Pair *)priorityQueue->arr[2]).priority == pair3.priority);
	assert((*(Pair *)priorityQueue->arr[2]).index == pair3.index);
	assert((*(Pair *)priorityQueue->arr[3]).priority == pair1.priority);
	assert((*(Pair *)priorityQueue->arr[3]).index == pair1.index);
	assert((*(Pair *)priorityQueue->arr[4]).priority == pair2.priority);
	assert((*(Pair *)priorityQueue->arr[4]).index == pair2.index);
	assert((*(Pair *)priorityQueue->arr[5]).priority == pair4.priority);
	assert((*(Pair *)priorityQueue->arr[5]).index == pair4.index);

	head_ = head(priorityQueue);
	assert(head_ != NULL);
	assert((*(Pair *)head_).priority == pair5.priority);
	assert((*(Pair *)head_).index == pair5.index);

	add(priorityQueue, (void *)&pair6);
	assert(priorityQueue->index == 6);
	assert((*(Pair *)priorityQueue->arr[1]).priority == pair5.priority);
	assert((*(Pair *)priorityQueue->arr[1]).index == pair5.index);
	assert((*(Pair *)priorityQueue->arr[2]).priority == pair3.priority);
	assert((*(Pair *)priorityQueue->arr[2]).index == pair3.index);
	assert((*(Pair *)priorityQueue->arr[3]).priority == pair1.priority);
	assert((*(Pair *)priorityQueue->arr[3]).index == pair1.index);
	assert((*(Pair *)priorityQueue->arr[4]).priority == pair2.priority);
	assert((*(Pair *)priorityQueue->arr[4]).index == pair2.index);
	assert((*(Pair *)priorityQueue->arr[5]).priority == pair4.priority);
	assert((*(Pair *)priorityQueue->arr[5]).index == pair4.index);
	assert((*(Pair *)priorityQueue->arr[6]).priority == pair6.priority);
	assert((*(Pair *)priorityQueue->arr[6]).index == pair6.index);

	head_ = head(priorityQueue);
	assert(head_ != NULL);
	assert((*(Pair *)head_).priority == pair5.priority);
	assert((*(Pair *)head_).index == pair5.index);

	add(priorityQueue, (void *)&pair7);
	assert(priorityQueue->index == 7);
	assert((*(Pair *)priorityQueue->arr[1]).priority == pair5.priority);
	assert((*(Pair *)priorityQueue->arr[1]).index == pair5.index);
	assert((*(Pair *)priorityQueue->arr[2]).priority == pair3.priority);
	assert((*(Pair *)priorityQueue->arr[2]).index == pair3.index);
	assert((*(Pair *)priorityQueue->arr[3]).priority == pair7.priority);
	assert((*(Pair *)priorityQueue->arr[3]).index == pair7.index);
	assert((*(Pair *)priorityQueue->arr[4]).priority == pair2.priority);
	assert((*(Pair *)priorityQueue->arr[4]).index == pair2.index);
	assert((*(Pair *)priorityQueue->arr[5]).priority == pair4.priority);
	assert((*(Pair *)priorityQueue->arr[5]).index == pair4.index);
	assert((*(Pair *)priorityQueue->arr[6]).priority == pair6.priority);
	assert((*(Pair *)priorityQueue->arr[6]).index == pair6.index);
	assert((*(Pair *)priorityQueue->arr[7]).priority == pair1.priority);
	assert((*(Pair *)priorityQueue->arr[7]).index == pair1.index);

	head_ = head(priorityQueue);
	assert(head_ != NULL);
	assert((*(Pair *)head_).priority == pair5.priority);
	assert((*(Pair *)head_).index == pair5.index);

	head_ = remove_head(priorityQueue);
	assert(head_ != NULL);
	assert((*(Pair *)head_).priority == pair5.priority);
	assert((*(Pair *)head_).index == pair5.index);

	head_ = head(priorityQueue);
	assert(head_ != NULL);
	assert((*(Pair *)head_).priority == pair7.priority);
	assert((*(Pair *)head_).index == pair7.index);
	
	head_ = remove_head(priorityQueue);
	assert(head_ != NULL);
	assert((*(Pair *)head_).priority == pair7.priority);
	assert((*(Pair *)head_).index == pair7.index);

	head_ = head(priorityQueue);
	assert(head_ != NULL);
	assert((*(Pair *)head_).priority == pair3.priority);
	assert((*(Pair *)head_).index == pair3.index);
	
	head_ = remove_head(priorityQueue);
	assert(head_ != NULL);
	assert((*(Pair *)head_).priority == pair3.priority);
	assert((*(Pair *)head_).index == pair3.index);

	head_ = head(priorityQueue);
	assert(head_ != NULL);
	assert((*(Pair *)head_).priority == pair1.priority);
	assert((*(Pair *)head_).index == pair1.index);

	assert(priorityQueue->index == 4);
	assert((*(Pair *)priorityQueue->arr[1]).priority == pair1.priority);
	assert((*(Pair *)priorityQueue->arr[1]).index == pair1.index);
	assert((*(Pair *)priorityQueue->arr[2]).priority == pair4.priority);
	assert((*(Pair *)priorityQueue->arr[2]).index == pair4.index);
	assert((*(Pair *)priorityQueue->arr[3]).priority == pair6.priority);
	assert((*(Pair *)priorityQueue->arr[3]).index == pair6.index);
	assert((*(Pair *)priorityQueue->arr[4]).priority == pair2.priority);
	assert((*(Pair *)priorityQueue->arr[4]).index == pair2.index);

	head_ = remove_head(priorityQueue);
	assert(head_ != NULL);
	assert((*(Pair *)head_).priority == pair1.priority);
	assert((*(Pair *)head_).index == pair1.index);

	head_ = head(priorityQueue);
	assert(head_ != NULL);
	assert((*(Pair *)head_).priority == pair4.priority);
	assert((*(Pair *)head_).index == pair4.index);

	assert(priorityQueue->index == 3);
	assert((*(Pair *)priorityQueue->arr[1]).priority == pair4.priority);
	assert((*(Pair *)priorityQueue->arr[1]).index == pair4.index);
	assert((*(Pair *)priorityQueue->arr[2]).priority == pair2.priority);
	assert((*(Pair *)priorityQueue->arr[2]).index == pair2.index);
	assert((*(Pair *)priorityQueue->arr[3]).priority == pair6.priority);
	assert((*(Pair *)priorityQueue->arr[3]).index == pair6.index);

	destroy(priorityQueue);
	free(priorityQueue);

	printf("Test end successfully\n");
}

int main(int argc, char const *argv[])
{
	test_priority_queue();
	return 0;
}