#ifndef UTILS_H
#define UTILS_H

#ifdef __linux__
#include <pthread.h>
#include <unistd.h>

typedef pthread_t THREAD_ID;
typedef pthread_cond_t CONDITION;
typedef pthread_mutex_t MUTEX;

#define WAIT pthread_cond_wait
#define SIGNAL pthread_cond_signal
#define BROADCAST pthread_cond_broadcast

#define LOCK pthread_mutex_lock
#define UNLOCK pthread_mutex_unlock
#define DESTROY_LOCK pthread_mutex_destroy

#define SLEEP	sleep
#define TIME	0.05

#define RET_VAL NULL
#else
#include <windows.h>

typedef HANDLE THREAD_ID;
typedef CONDITION_VARIABLE CONDITION;
typedef CRITICAL_SECTION MUTEX;

#define WAIT SleepConditionVariableCS
#define SIGNAL WakeConditionVariable
#define BROADCAST WakeAllConditionVariable

#define LOCK EnterCriticalSection
#define UNLOCK LeaveCriticalSection
#define DESTROY_LOCK DeleteCriticalSection

#define SLEEP	Sleep
#define TIME	50

#define RET_VAL 0
#endif /* __linux__ */

#include "../../../PriorityQueue/PriorityQueue.h"
#include "../../../Logger/Logger.h"

#define SUCCESS	0
#define ERROR_	(-1)
#define MAX_THREADS	10000
#define INVALID_INDEX	(-1)
#define INVALID_EVENT	(-1)

/*
 * Starile in care poate fi, la fiecare moment de timp,
 * un thread introdus in sistem printr-un apel so_fork.
 */
typedef enum {
	NEW,
	READY,
	RUNNING,
	WAITING,
	TERMINATED
} STATE;

/*
 * Starile in care poate fi planificatorul la fiecare
 * moment de timp.
 * Stare NOT_YET sugereaza faptul ca inca nu s-a efectuat
 * primul apel de so_fork (din contextul testelor) care
 * introduce primul thread in sistem. Stare START marcheaza
 * faptul ca s-a creat primul thread si a fost introdus in
 * sistem. Starea END marcheaza faptul ca toate thread-urile
 * s-au terminat, anuntand planificatorul (vezi so_end) ca
 * poate elibera resursele utilizate.
 */
typedef enum {
	NOT_YET,
	START,
	END
} SCH_STATE;

/*
 * Descrie structura argumentului primit de functia
 * handler (vezi thread_func). Campul func reprezinta
 * un pointer la functia pe care o va executa noul
 * thread introdus in planificator. Iar campul node
 * retine informatiile care caracterizeaza noul thread,
 * precum: prioritate, index, timestamp.
 */
typedef struct {
	so_handler *func;
	Node node;
} th_func_arg_t;

/*
 * Structura ce descrie caracteristicile fiecarui thread
 * din sistemul planificator:
 * prioritatea, cuanta de timp curenta, starea, evenimentul
 * sau operatia IO la care s-a blocat(deci cand este in starea
 * WAITING), id-ul thread-ului de sistem.
 */
typedef struct {
	unsigned int priority;
	int c_t_qu;
	STATE state;
	int event;
	THREAD_ID thread_id;
} thread_t;

/*
 * Structura ce descrie sistemul planificator.
 * Caracteristicile acestuia sunt:
 * numarul de thread-uri pe care le are in subordine
 * la fiecare moment de timp; cuanta de timp dupa care
 * fiecare thread aflat in RUNNING va trebui sa fie
 * preemptat; numarul de evenimente suportate; starea;
 * timestamp ajuta la implementarea modelului Round
 * Robin pentru thread-urile cu aceeasi prioritate
 * (pentru detalii vezi structura Node); un vector
 * de thread-uri; coada READY; componenta de logging
 * elementele de sincronizare, care asigura ca la
 * fiecare moment de timp exista un singur thread
 * aflat in starea RUNNING, respectiv, asteptarea
 * terminarii tuturor thread-urilor inainte de
 * parasirea sistemului.
 */
typedef struct {
	unsigned int nr_threads;
	unsigned int t_qu;
	unsigned int nr_events;
	SCH_STATE state;
	unsigned int timestamp;
	thread_t *threads;
	PriorityQueue *ready_q;
	Logger *logger;
	CONDITION cond_running;
	MUTEX mutex_running;
	CONDITION cond_end;
	MUTEX mutex_end;
} scheduler_t;

#endif /* UTILS_H */
