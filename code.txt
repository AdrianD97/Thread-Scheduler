//========================
printf("Thread %d zice ca avem: ", node.index);
for (int i = 1; i <= scheduler->ready_queue->index; ++i) {
	printf("(ind, prio, time)=(%d, %d, %d) ", scheduler->ready_queue->arr[i].index,
		scheduler->ready_queue->arr[i].priority,
		scheduler->ready_queue->arr[i].timestamp);
}
printf("\n, next is %d\n", pr->index);
//========================