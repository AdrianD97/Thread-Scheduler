#include "heap_util.h"

int compare_pairs(Pair *pair1, Pair *pair2)
{
	return pair1->priority - pair2->priority;
}
