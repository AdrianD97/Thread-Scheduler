#include <stdio.h>
#include <assert.h>

#include "utils/utils.h"
#include "PriorityQueue/PriorityQueue.h"

void test_priority_queue()
{
	printf("Start test.\n");

	Node node1, node2, node3, node4, node5, node6, node7;

	node1.index = 0;
	node1.priority = 3;

	node2.index = 1;
	node2.priority = 2;

	node3.index = 2;
	node3.priority = 5;

	node4.index = 3;
	node4.priority = 3;

	node5.index = 4;
	node5.priority = 8;

	node6.index = 5;
	node6.priority = 0;

	node7.index = 6;
	node7.priority = 8;

	Node const *head_;
	Node root;
	PriorityQueue *priorityQueue;
	int size = 10;

	priorityQueue = createPriorityQueue(size);
	assert(priorityQueue != NULL);
	assert(priorityQueue->size == size);
	assert(priorityQueue->index == 0);
	assert(priorityQueue->compare == compare_pairs);
	assert(priorityQueue->arr != NULL);

	add(priorityQueue, node1);
	assert(priorityQueue->index == 1);
	assert(priorityQueue->arr[1].priority == node1.priority);
	assert(priorityQueue->arr[1].index == node1.index);

	head_ = head(priorityQueue);
	assert(head_ != NULL);
	assert(head_->priority == node1.priority);
	assert(head_->index == node1.index);

	add(priorityQueue, node2);
	assert(priorityQueue->index == 2);
	assert(priorityQueue->arr[1].priority == node1.priority);
	assert(priorityQueue->arr[1].index == node1.index);
	assert(priorityQueue->arr[2].priority == node2.priority);
	assert(priorityQueue->arr[2].index == node2.index);

	head_ = head(priorityQueue);
	assert(head_ != NULL);
	assert(head_->priority == node1.priority);
	assert(head_->index == node1.index);

	add(priorityQueue, node3);
	assert(priorityQueue->index == 3);
	assert(priorityQueue->arr[1].priority == node3.priority);
	assert(priorityQueue->arr[1].index == node3.index);
	assert(priorityQueue->arr[2].priority == node2.priority);
	assert(priorityQueue->arr[2].index == node2.index);
	assert(priorityQueue->arr[3].priority == node1.priority);
	assert(priorityQueue->arr[3].index == node1.index);

	head_ = head(priorityQueue);
	assert(head_ != NULL);
	assert(head_->priority == node3.priority);
	assert(head_->index == node3.index);
	
	add(priorityQueue, node4);
	assert(priorityQueue->index == 4);
	assert(priorityQueue->arr[1].priority == node3.priority);
	assert(priorityQueue->arr[1].index == node3.index);
	assert(priorityQueue->arr[2].priority == node4.priority);
	assert(priorityQueue->arr[2].index == node4.index);
	assert(priorityQueue->arr[3].priority == node1.priority);
	assert(priorityQueue->arr[3].index == node1.index);
	assert(priorityQueue->arr[4].priority == node2.priority);
	assert(priorityQueue->arr[4].index == node2.index);

	head_ = head(priorityQueue);
	assert(head_ != NULL);
	assert(head_->priority == node3.priority);
	assert(head_->index == node3.index);
	
	add(priorityQueue, node5);
	assert(priorityQueue->index == 5);
	assert(priorityQueue->arr[1].priority == node5.priority);
	assert(priorityQueue->arr[1].index == node5.index);
	assert(priorityQueue->arr[2].priority == node3.priority);
	assert(priorityQueue->arr[2].index == node3.index);
	assert(priorityQueue->arr[3].priority == node1.priority);
	assert(priorityQueue->arr[3].index == node1.index);
	assert(priorityQueue->arr[4].priority == node2.priority);
	assert(priorityQueue->arr[4].index == node2.index);
	assert(priorityQueue->arr[5].priority == node4.priority);
	assert(priorityQueue->arr[5].index == node4.index);

	head_ = head(priorityQueue);
	assert(head_ != NULL);
	assert(head_->priority == node5.priority);
	assert(head_->index == node5.index);

	add(priorityQueue, node6);
	assert(priorityQueue->index == 6);
	assert(priorityQueue->arr[1].priority == node5.priority);
	assert(priorityQueue->arr[1].index == node5.index);
	assert(priorityQueue->arr[2].priority == node3.priority);
	assert(priorityQueue->arr[2].index == node3.index);
	assert(priorityQueue->arr[3].priority == node1.priority);
	assert(priorityQueue->arr[3].index == node1.index);
	assert(priorityQueue->arr[4].priority == node2.priority);
	assert(priorityQueue->arr[4].index == node2.index);
	assert(priorityQueue->arr[5].priority == node4.priority);
	assert(priorityQueue->arr[5].index == node4.index);
	assert(priorityQueue->arr[6].priority == node6.priority);
	assert(priorityQueue->arr[6].index == node6.index);

	head_ = head(priorityQueue);
	assert(head_ != NULL);
	assert(head_->priority == node5.priority);
	assert(head_->index == node5.index);

	add(priorityQueue, node7);
	assert(priorityQueue->index == 7);
	assert(priorityQueue->arr[1].priority == node5.priority);
	assert(priorityQueue->arr[1].index == node5.index);
	assert(priorityQueue->arr[2].priority == node3.priority);
	assert(priorityQueue->arr[2].index == node3.index);
	assert(priorityQueue->arr[3].priority == node7.priority);
	assert(priorityQueue->arr[3].index == node7.index);
	assert(priorityQueue->arr[4].priority == node2.priority);
	assert(priorityQueue->arr[4].index == node2.index);
	assert(priorityQueue->arr[5].priority == node4.priority);
	assert(priorityQueue->arr[5].index == node4.index);
	assert(priorityQueue->arr[6].priority == node6.priority);
	assert(priorityQueue->arr[6].index == node6.index);
	assert(priorityQueue->arr[7].priority == node1.priority);
	assert(priorityQueue->arr[7].index == node1.index);

	head_ = head(priorityQueue);
	assert(head_ != NULL);
	assert(head_->priority == node5.priority);
	assert(head_->index == node5.index);

	root = remove_head(priorityQueue);
	assert(root.priority == node5.priority);
	assert(root.index == node5.index);

	head_ = head(priorityQueue);
	assert(head_ != NULL);
	assert(head_->priority == node7.priority);
	assert(head_->index == node7.index);
	
	root = remove_head(priorityQueue);
	assert(root.priority == node7.priority);
	assert(root.index == node7.index);

	head_ = head(priorityQueue);
	assert(head_ != NULL);
	assert(head_->priority == node3.priority);
	assert(head_->index == node3.index);
	assert(priorityQueue->index == 5);
	assert(priorityQueue->arr[1].priority == node3.priority);
	assert(priorityQueue->arr[1].index == node3.index);
	assert(priorityQueue->arr[2].priority == node4.priority);
	assert(priorityQueue->arr[2].index == node4.index);
	assert(priorityQueue->arr[3].priority == node1.priority);
	assert(priorityQueue->arr[3].index == node1.index);
	assert(priorityQueue->arr[4].priority == node2.priority);
	assert(priorityQueue->arr[4].index == node2.index);
	assert(priorityQueue->arr[5].priority == node6.priority);
	assert(priorityQueue->arr[5].index == node6.index);
	
	root = remove_head(priorityQueue);
	assert(root.priority == node3.priority);
	assert(root.index == node3.index);

	head_ = head(priorityQueue);
	assert(head_ != NULL);
	assert(head_->priority == node1.priority);
	assert(head_->index == node1.index);

	assert(priorityQueue->index == 4);
	assert(priorityQueue->arr[1].priority == node1.priority);
	assert(priorityQueue->arr[1].index == node1.index);
	assert(priorityQueue->arr[2].priority == node4.priority);
	assert(priorityQueue->arr[2].index == node4.index);
	assert(priorityQueue->arr[3].priority == node6.priority);
	assert(priorityQueue->arr[3].index == node6.index);
	assert(priorityQueue->arr[4].priority == node2.priority);
	assert(priorityQueue->arr[4].index == node2.index);

	root = remove_head(priorityQueue);
	assert(root.priority == node1.priority);
	assert(root.index == node1.index);

	head_ = head(priorityQueue);
	assert(head_ != NULL);
	assert(head_->priority == node4.priority);
	assert(head_->index == node4.index);

	assert(priorityQueue->index == 3);
	assert(priorityQueue->arr[1].priority == node4.priority);
	assert(priorityQueue->arr[1].index == node4.index);
	assert(priorityQueue->arr[2].priority == node2.priority);
	assert(priorityQueue->arr[2].index == node2.index);
	assert(priorityQueue->arr[3].priority == node6.priority);
	assert(priorityQueue->arr[3].index == node6.index);

	destroy(priorityQueue);
	free(priorityQueue);

	printf("Test end successfully\n");
}

int main(int argc, char const *argv[])
{
	test_priority_queue();
	return 0;
}