#ifndef UTILS_H
#define UTILS_H

#include <pthread.h>

#include "../PriorityQueue/PriorityQueue.h"

#define SUCCESS	0
#define ERROR	(-1)
#define MAX_THREADS	10000
#define INVALID_INDEX	(-1)
#define INVALID_EVENT	(-1)

#define PREEMPTED 		1
#define NO_PREEMPTED	0

typedef enum {
	NEW,
	READY,
	RUNNING,
	WAITING,
	TERMINATED
} STATE;

typedef struct {
	so_handler *func;
	Node node;
} th_func_arg;

typedef struct {
	unsigned int priority;
	int current_time_quantum;
	STATE state;
	unsigned int event;
	unsigned char preempted;
	pthread_t thread_id;
} thread_t;

typedef struct {
	unsigned int nr_threads;
	unsigned int time_quantum;
	unsigned int nr_events;
	unsigned int current_thread; /* index in array-ul de thread-uri */
	unsigned int timestamp;
	thread_t *threads;
	PriorityQueue *ready_queue;
	/*ADD syncroniziny elements*/
	/*
	1. Variabila conditie care sa permita unui singur thread sa fie in RUNNING la fiecare
	moment de timp
	2. O variabila folosita in so_fork si start_thread/thread_function pentru a notifica parintele
	ca noul copil a intrat in READY/RUNNING
	*/
	pthread_cond_t cond_running;
	pthread_cond_t cond_parent_child;
	pthread_mutex_t mutex_running;
	pthread_mutex_t mutex_parent_child;
} scheduler_t;

#endif // UTILS_H
