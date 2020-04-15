#ifndef HEAP_UTIL_H_
#define HEAP_UTIL_H_

typedef struct {
	unsigned int index;
	unsigned int priority;
	unsigned int timestamp;
} Node;

int compare_pairs(Node *node1, Node *node2);

#endif /* HEAP_UTIL_H_ */
