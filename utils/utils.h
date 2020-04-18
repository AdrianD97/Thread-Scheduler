#ifndef UTILS_H
#define UTILS_H

#ifdef __linux__
#include <pthread.h>

typedef void* RET_FUNC_T;
typedef void* ARG_FUNC_T;

typedef pthread_t THREAD_ID;
typedef pthread_cond_t CONDITION;
typedef pthread_mutex_t MUTEX;

#define WAIT pthread_cond_wait
#define SIGNAL pthread_cond_signal
#define BROADCAST pthread_cond_broadcast

#define LOCK pthread_mutex_lock
#define UNLOCK pthread_mutex_unlock
#define DESTROY_LOCK pthread_mutex_destroy

#define GetThreadId pthread_self

#define RET_VAL NULL
#else
#include <windows.h>

typedef DWORD WINAPI RET_FUNC_T;
typedef LPVOID ARG_FUNC_T;

typedef HANDLE THREAD_ID;
typedef CONDITION_VARIABLE CONDITION;
typedef CRITICAL_SECTION MUTEX;

#define WAIT SleepConditionVariableCS
#define SIGNAL WakeConditionVariable
#define BROADCAST WakeAllConditionVariable

#define LOCK EnterCriticalSection
#define UNLOCK LeaveCriticalSection
#define DESTROY_LOCK DeleteCriticalSection

#define GetThreadId GetCurrentThread

#define RET_VAL 0
#endif /* __linux__ */

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
	THREAD_ID thread_id;
} thread_t;

typedef struct {
	unsigned int nr_threads;
	unsigned int t_qu;
	unsigned int nr_events;
	SCH_STATE state;
	unsigned int timestamp;
	thread_t *threads;
	PriorityQueue *ready_q;
	CONDITION cond_running;
	MUTEX mutex_running;
	CONDITION cond_end;
	MUTEX mutex_end;
} scheduler_t;

#endif /* UTILS_H */
