#ifndef HEAP_UTIL_H_
#define HEAP_UTIL_H_

typedef struct {
	unsigned int index;
	unsigned int priority;
} Pair;

int compare_pairs(Pair *pair1, Pair *pair2);

#endif /* HEAP_UTIL_H_ */
