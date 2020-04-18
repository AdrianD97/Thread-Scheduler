#ifndef UTILS_H
#define UTILS_H

#include <pthread.h>

#include "../PriorityQueue/PriorityQueue.h"

#define SUCCESS	0
#define ERROR_	(-1)
#define MAX_THREADS	10000
#define INVALID_INDEX	(-1)
#define INVALID_EVENT	(-1)

#define PREEMPTED		1
#define NO_PREEMPTED	0

typedef enum {
	NEW,
	READY,
	RUNNING,
	WAITING,
	TERMINATED
} STATE;

typedef enum {
	NOT_YET,
	START,
	END
} SCH_STATE;

typedef struct {
	so_handler *func;
	Node node;
} th_func_arg_t;

typedef struct {
	unsigned int priority;
	int c_t_qu;
	STATE state;
	int event;
	unsigned char preempted;
	pthread_t thread_id;
} thread_t;

typedef struct {
	unsigned int nr_threads;
	unsigned int t_qu;
	unsigned int nr_events;
	SCH_STATE state;
	unsigned int timestamp;
	thread_t *threads;
	PriorityQueue *ready_q;
	pthread_cond_t cond_running;
	pthread_mutex_t mutex_running;
	pthread_cond_t cond_end;
	pthread_mutex_t mutex_end;
} scheduler_t;

#endif // UTILS_H
