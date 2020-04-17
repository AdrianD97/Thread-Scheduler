#include "Heap.h"

Heap *createEmptyHeap(int size)
{
	Heap *heap = (Heap *)malloc(sizeof(Heap));

	if (!heap)
		return NULL;

	heap->size = size;
	heap->index = 0;
	heap->compare = compare_nodes;
	heap->arr = (Node *)malloc((size + 1) * sizeof(Node));
	if (!heap->arr) {
		free(heap);
		return NULL;
	}

	return heap;
}

static void pushUp(Heap *heap, int type)
{
	int index = heap->index;
	int parent, result = 0;
	Node tmp;

	do {
		parent = index / 2;

		if (parent == 0)
			break;

		result = heap->compare(&heap->arr[index],
			&heap->arr[parent]);

		if (type == MIN_HEAP) { /* heap is min heap */
			if (result >= 0)
				break;
		} else { /* heap is max heap */
			if (result <= 0)
				break;
		}

		tmp = heap->arr[index];
		heap->arr[index] = heap->arr[parent];
		heap->arr[parent] = tmp;
		index = parent;
	} while (1);
}

/*
 *	type = MIN_HEAP -> heap is a min heap
 *	type = MAX_HEAP -> heap is a max heap
 */
void addItemToHeap(Heap *heap, Node value, int type)
{
	if (!heap ||
		(type != MAX_HEAP && type != MIN_HEAP))
		return;

	/* check if Heap is full */
	if (heap->index + 1 > heap->size)
		return;

	heap->arr[++heap->index] = value;
	pushUp(heap, type);
}

Node const *getHeapRoot(const Heap *heap)
{
	if (!heap || heap->index == 0)
		return NULL;

	return (Node const *)&heap->arr[ROOT];
}

static void pushDown(Heap *heap, int type)
{
	if (heap->index == 0)
		return;

	int index = ROOT, result;
	int child_ind, result_;
	Node tmp;

	do {
		if (2 * index <= heap->index) {
			if (2 * index + 1 > heap->index) {
				result = heap->compare(&heap->arr[index],
					&heap->arr[2 * index]);
				child_ind = 2 * index;
			} else {
				result_ = heap->compare(&heap->arr[2 * index],
					&heap->arr[2 * index + 1]);

				if (type == MIN_HEAP) /* heap is min heap */
					child_ind = (result_ < 0) ? (2 * index)
							: (2 * index + 1);
				else /* heap is max heap */
					child_ind = (result_ > 0) ? (2 * index)
							: (2 * index + 1);

				result = heap->compare(&heap->arr[index],
					&heap->arr[child_ind]);
			}

			if (type == MIN_HEAP) { /* heap is min heap */
				if (result <= 0)
					break;
			} else { /* heap is max heap */
				if (result >= 0)
					break;
			}

			tmp = heap->arr[index];
			heap->arr[index] = heap->arr[child_ind];
			heap->arr[child_ind] = tmp;
			index = child_ind;
		} else
			break;

	} while (1);
}

/*
 *	type = MIN_HEAP -> heap is a min heap
 *	type = MAX_HEAP -> heap is a max heap
 */
Node removeHeapRoot(Heap *heap, int type)
{
	Node tmp;

	tmp.index = tmp.priority = tmp.timestamp = 0;

	if (!heap || !heap->arr || heap->index == 0
		|| (type != MAX_HEAP && type != MIN_HEAP))
		return tmp;

	tmp = heap->arr[ROOT];
	heap->arr[ROOT] = heap->arr[heap->index];
	heap->arr[heap->index] = tmp;

	--heap->index;
	pushDown(heap, type);

	return tmp;
}

void freeHeapMemory(Heap *heap)
{
	if (!heap || !heap->arr)
		return;

	free(heap->arr);
	heap->arr = NULL;
}
