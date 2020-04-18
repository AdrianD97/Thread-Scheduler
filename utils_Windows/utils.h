#ifndef UTILS_H
#define UTILS_H

#include <windows.h>
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
	HANDLE thread_id;
} thread_t;

typedef struct {
	unsigned int nr_threads;
	unsigned int t_qu;
	unsigned int nr_events;
	SCH_STATE state;
	unsigned int timestamp;
	thread_t *threads;
	PriorityQueue *ready_q;
	CONDITION_VARIABLE cond_running;
	CRITICAL_SECTION mutex_running;
	CONDITION_VARIABLE cond_end;
	CRITICAL_SECTION mutex_end;
} scheduler_t;

#endif // UTILS_H
