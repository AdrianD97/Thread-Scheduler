#include "heap_util.h"

int compare_nodes(Node *node1, Node *node2)
{
	int res = node1->priority - node2->priority;

	return (res == 0) ? (node2->timestamp - node1->timestamp) : res;
}
