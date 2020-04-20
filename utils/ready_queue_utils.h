#ifndef READY_QUEUE_UTILS_H_
#define READY_QUEUE_UTILS_H_

/*
 * descrie structura unui node din heap.
 * caracteristicile noudului sunt:
 * un index, utilizat pentru a identifica
 * un thread in cadrul array-ului de thread-uri
 * din sistemul de planificator; prioritatea
 * folosita pentru a ordona thread-urile in cazul
 * cozii READY; timestamp - util in cazul in care
 * doua thread-uri au aceeasi prioritate, pentru
 * ca acestea sa poata fi planificate dupa modelul
 * Round Robin.
 */
typedef struct {
	unsigned int index;
	unsigned int priority;
	unsigned int timestamp;
} Node;

/*
 * compara doua noduri dupa prioritatea
 * si/sau timestamp-ul acestora.
 * Functia este utila in crearea structurii
 * de heap(maxheap mai exact) care sta la
 * baza implementarii cozii de prioritate
 * (coada READY).
 */
int compare_nodes(Node *node1, Node *node2);

#endif /* READY_QUEUE_UTILS_H_ */
