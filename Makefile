CC = gcc
CFLAGS = -fPIC -Wall

.PHONY: build
build: libscheduler.so

libscheduler.so: so_scheduler.o PriorityQueue.o Heap.o heap_util.o
	$(CC) -shared -o $@ $^

heap_util.o: PriorityQueue/Heap/heap_util.c
	$(CC) $(CFLAGS) -o $@ -c $^

Heap.o: PriorityQueue/Heap/Heap.c
	$(CC) $(CFLAGS) -o $@ -c $^

PriorityQueue.o: PriorityQueue/PriorityQueue.c
	$(CC) $(CFLAGS) -o $@ -c $^

so_scheduler.o: so_scheduler.c
	$(CC) $(CFLAGS) -o $@ -c $^

.PHONY: clean
clean:
	rm -f so_scheduler.o PriorityQueue.o Heap.o heap_util.o libscheduler.so
