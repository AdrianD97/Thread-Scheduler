SOURCES=test_so_scheduler.c so_scheduler.c PriorityQueue/PriorityQueue.c PriorityQueue/Heap/Heap.c

test_so_scheduler: $(SOURCES)
	gcc -Wall $^ -o $@ -lpthread

clean:
	rm -f test_so_scheduler *.o
