CC = gcc
CFLAGS = -fPIC -Wall

.PHONY: build
build: libscheduler.so

libscheduler.so: so_scheduler.o PriorityQueue.o Heap.o ready_queue_utils.o
	$(CC) -shared -o $@ $^

ready_queue_utils.o: utils/ready_queue_utils.c
	$(CC) $(CFLAGS) -o $@ -c $^

Heap.o: PriorityQueue/Heap/Heap.c
	$(CC) $(CFLAGS) -o $@ -c $^

PriorityQueue.o: PriorityQueue/PriorityQueue.c
	$(CC) $(CFLAGS) -o $@ -c $^

so_scheduler.o: so_scheduler.c
	$(CC) $(CFLAGS) -o $@ -c $^

.PHONY: clean
clean:
	rm -f so_scheduler.o PriorityQueue.o Heap.o ready_queue_utils.o libscheduler.so
