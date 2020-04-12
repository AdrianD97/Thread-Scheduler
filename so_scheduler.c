/* TODO: Only testing ppurpose */
#include <stdio.h>
/* TODO: End of testing code */

#include "so_scheduler.h"
#include "utils/utils.h"

pthread_mutexattr_t attr;

static scheduler_t *scheduler;

int so_init(unsigned int time_quantum, unsigned int io)
{
	printf("[SO_SCHEDULER]: Fac si eu o initializare corespunzatoare.\n");
	int ret1, ret2;

	if (io >= SO_MAX_NUM_EVENTS)
		return ERROR;

	scheduler = (scheduler_t *)malloc(sizeof(scheduler_t));
	if (!scheduler)
		return ERROR;

	scheduler->nr_threads = 0;
	scheduler->time_quantum = time_quantum;
	scheduler->nr_events = io;
	scheduler->current_thread = INVALID_INDEX;
	
	scheduler->threads = (thread_t *)malloc(MAX_THREADS * sizeof(thread_t));
	if (!scheduler->threads) {
		free(scheduler);
		return ERROR;
	}

	scheduler->ready_queue = createPriorityQueue(MAX_THREADS);
	if (!scheduler->ready_queue) {
		free(scheduler->threads);
		free(scheduler);
		return ERROR;
	}

	ret1 = pthread_cond_init(&scheduler->cond_running, NULL);
	ret2 = pthread_cond_init(&scheduler->cond_parent_child, NULL);
	if (ret1 | ret2) {
		destroy(scheduler->ready_queue);
		free(scheduler->ready_queue);
		free(scheduler->threads);
		if (ret1)
			pthread_cond_destroy(&scheduler->cond_parent_child);

		if (ret2)
			pthread_cond_destroy(&scheduler->cond_running);

		free(scheduler);
		return ERROR;
	}

	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

	ret1 = pthread_mutex_init(&scheduler->mutex_running, &attr);
	ret2 = pthread_mutex_init(&scheduler->mutex_parent_child, NULL);

	if (ret1 | ret2) {
		destroy(scheduler->ready_queue);
		free(scheduler->ready_queue);
		free(scheduler->threads);
		pthread_cond_destroy(&scheduler->cond_parent_child);
		pthread_cond_destroy(&scheduler->cond_running);
		if (ret1)
			pthread_mutex_destroy(&scheduler->mutex_parent_child);

		if (ret2)
			pthread_mutex_destroy(&scheduler->mutex_running);
			
		free(scheduler);
		return ERROR;
	}

	return SUCCESS;
}

static void* thread_func(void *arg)
{
	printf("[THREAD_FUNCTION]: Thread %d i'am here. Because sunt creat.\n",
		scheduler->nr_threads);

	Pair pair;
	Pair const *pr;
	unsigned int q;
	int preempted = 0, first = 0;
	so_handler *handler = (so_handler *)arg;

	pthread_mutex_lock(&scheduler->mutex_parent_child);
	pair.index = scheduler->nr_threads;
	++scheduler->nr_threads;
	pair.priority = scheduler->threads[pair.index].priority;

	scheduler->threads[pair.index].thread_id = pthread_self();

	scheduler->threads[pair.index].state = READY;
	add(scheduler->ready_queue, pair);

	if (scheduler->current_thread != INVALID_INDEX) {
		q = --scheduler->threads[scheduler->current_thread].current_time_quantum;
		if (q == 0) { /* Trebuie sa verific si daca nu cumva cel din head are o prioritate mai mica decat a mea
					caz in care nu ma preemptez, sau daca coada este vida*/
			pr = head(scheduler->ready_queue);
			if (pr && pr->priority >= scheduler->threads[scheduler->current_thread].priority) {
				preempted = 1;
			}
		}

		if (pair.priority > scheduler->threads[scheduler->current_thread].priority)
			preempted = 1;
	} else
		first = 1;

	if (preempted) {
		scheduler->threads[scheduler->current_thread].state = READY;
		scheduler->current_thread = pair.index;
		scheduler->threads[pair.index].current_time_quantum = scheduler->time_quantum;
		scheduler->threads[pair.index].state = RUNNING;
	}

	printf("[THREAD_FUNCTION]: Thread %d semanalizez ca am intrat in READY, poate chiar RUNNING.\n",
		pair.index);
	pthread_cond_signal(&scheduler->cond_parent_child);
	pthread_mutex_unlock(&scheduler->mutex_parent_child);

	printf("[THREAD_FUNCTION]: Thread %d sunt chiar inainte de mutex mutex_running.\n", pair.index);
	// wait to be scheduled
	pthread_mutex_lock(&scheduler->mutex_running);
	printf("[THREAD_FUNCTION]: Thread %d am intrat in mutex mutex_running.\n", pair.index);
	if (first) {
		scheduler->current_thread = pair.index;
		scheduler->threads[pair.index].current_time_quantum = scheduler->time_quantum;
		scheduler->threads[pair.index].state = RUNNING;
	}

	/*
	///////////////////////
	*/
	int ind = pair.index;
	/*
	//////////////
	*/
	printf("[THREAD_FUNCTION]: Thread %d ma pregatesc sa astept RUNNING.\n", ind);
	while (scheduler->threads[pair.index].state != RUNNING) {
		printf("[THREAD_FUNCTION]: Thread %d astept RUNNING.\n", ind);
		pthread_cond_wait(&scheduler->cond_running,
			&scheduler->mutex_running);
	}

	// pair = remove_head(scheduler->ready_queue);
	// add(scheduler->ready_queue, pair);

	/*TODO OBS: El o sa fie blocat in alte functii 
	pentru ca voi face wait la inceputul functiilor 
	ca starea lui sa devina RUNNING */
	printf("[THREAD_FUNCTION]: Thread %d apelez imediat handler-furnizat prin arg.\n", ind);
	handler(pair.priority);

	pair = remove_head(scheduler->ready_queue);
	scheduler->threads[pair.index].state = TERMINATED;

	// get another thread
	pr = head(scheduler->ready_queue);
	if (pr) {
		printf("[THREAD_FUNCTION]: Thread %d zice ca avem in heap: ", ind);
		for (int i = 1; i <= scheduler->ready_queue->index; ++i) {
			printf("(%d, %d) ", scheduler->ready_queue->arr[i].index, scheduler->ready_queue->arr[i].priority);
		}
		printf("\n");
		printf("[THREAD_FUNCTION]: Thread %d da procesorul altuia pentru ca eu m-am terminat.\n", ind);
		//pair = remove_head(scheduler->ready_queue);
		printf("[THREAD_FUNCTION]: Thread %d zice ca noul este: %d\n", ind, pr->index);
		// scheduler->current_thread = pair.index;
		// scheduler->threads[pair.index].state = RUNNING;
		scheduler->current_thread = pr->index;
		scheduler->threads[pr->index].state = RUNNING;
		//add(scheduler->ready_queue, pair);

		printf("[THREAD_FUNCTION SECOND ]: Thread %d zice ca avem in heap: ", ind);
		for (int i = 1; i <= scheduler->ready_queue->index; ++i) {
			printf("(%d, %d) ", scheduler->ready_queue->arr[i].index, scheduler->ready_queue->arr[i].priority);
		}
		printf("\n");
		pthread_cond_signal(&scheduler->cond_running);
	}
	pthread_mutex_unlock(&scheduler->mutex_running);
	printf("[THREAD_FUNCTION]: Thread %d am terminat\n", ind);
	return NULL;
}

tid_t so_fork(so_handler *func, unsigned int priority)
{
	printf("[SO_FORK]: Thread %d start a new thread, deci va primi index: %d\n",
		scheduler->current_thread, scheduler->nr_threads);

	int ret, crt_thread, nr, wait;
	tid_t thread_id;

	if (!func)
		return INVALID_TID;

	wait = 0;
	nr = scheduler->nr_threads;
	crt_thread = scheduler->current_thread;
	scheduler->threads[nr].priority = priority;
	scheduler->threads[nr].current_time_quantum = scheduler->time_quantum;
	scheduler->threads[nr].state = NEW;
	scheduler->threads[nr].event = INVALID_EVENT;

	ret = pthread_create(&thread_id, NULL, thread_func, (void *)func);
	if (ret)
		return INVALID_TID;

	// wait
	pthread_mutex_lock(&scheduler->mutex_parent_child);
	printf("[SO_FORK]: Thread %d astept sa fie odrasla programata.\n", crt_thread);
	
	while (scheduler->threads[nr].state != READY
		&& scheduler->threads[nr].state != RUNNING
		&& scheduler->threads[nr].state != TERMINATED) {
		printf("[SO_FORK]: Thread %d confirm stare odrasal, state: %d\n",
			crt_thread, scheduler->threads[nr].state);
		pthread_cond_wait(&scheduler->cond_parent_child,
			&scheduler->mutex_parent_child);
	}

	pthread_mutex_unlock(&scheduler->mutex_parent_child);

	printf("[SO_FORK]: Thread %d iau mutexul mutex_running sau nu \n", crt_thread);
	pthread_mutex_lock(&scheduler->mutex_running);
	while (crt_thread != INVALID_INDEX &&
		scheduler->threads[crt_thread].state != RUNNING) {
		// printf("Stau si astept pentru ca m-a blocat cineva. -> STATE = %d, crt_thread = %d\n",
			// scheduler->threads[crt_thread].state, crt_thread);
		//
		pthread_mutex_unlock(&scheduler->mutex_running);
		wait = 1;
		//
		pthread_cond_wait(&scheduler->cond_running,
			&scheduler->mutex_running);
	}

	if (wait) {
		pthread_mutex_lock(&scheduler->mutex_running);
	}
	printf("[SO_FORK]: Thread %d il voi debloca imediat pe mutex_running.\n", crt_thread);
	pthread_mutex_unlock(&scheduler->mutex_running);
	return thread_id;
}

void so_end(void)
{
	printf("[SO_SCHEDULER]: Fac si eu o dezalocare corespunzatoare.\n");
	if (!scheduler)
		return;

	for (int i = 0; i < scheduler->nr_threads; ++i) {
		pthread_join(scheduler->threads[i].thread_id, NULL);
	}

	destroy(scheduler->ready_queue);
	free(scheduler->ready_queue);
	free(scheduler->threads);
	pthread_cond_destroy(&scheduler->cond_running);
	pthread_cond_destroy(&scheduler->cond_parent_child);
	pthread_mutex_destroy(&scheduler->mutex_running);
	pthread_mutex_destroy(&scheduler->mutex_parent_child);
	free(scheduler);
	scheduler = NULL;
}
