/* TODO: Only testing ppurpose */
#include <stdio.h>
/* TODO: End of testing code */

/* TODO: Daca nu mrege conversia lui 0 la Pair atunci fac o functie in 
Heap care sa imi spuna daca este sau nu empty*/

#include "so_scheduler.h"
#include "utils/utils.h"

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
	scheduler->current_thread = INVLAID_INDEX;
	
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

	ret1 = pthread_mutex_init(&scheduler->mutex_running, NULL);
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
	Pair pair;
	unsigned int q;
	int preempted = 0, first = 0;
	so_handler *handler = (so_handler *)arg;

	pthread_mutex_lock(&scheduler->mutex_parent_child);
	pair.index = scheduler->nr_threads;
	pair.priority = scheduler->threads[pair.index].priority;

	scheduler->threads[pair.index].thread_id = pthread_self();

	scheduler->threads[pair.index].state = READY;
	add(scheduler->ready_queue, pair);

	if (scheduler->current_thread != INVLAID_INDEX) {
		q = --scheduler->threads[scheduler->current_thread].current_time_quantum;
		if (q == 0)
			preempted = 1;

		if (pair.priority > scheduler->threads[scheduler->current_thread].priority)
			preempted = 1;
	} else
		first = 1;

	if (preempted) {
		scheduler->current_thread = pair.index;
		scheduler->threads[pair.index].current_time_quantum = scheduler->time_quantum;
		scheduler->threads[pair.index].state = RUNNING;
	}
	pthread_cond_signal(&scheduler->cond_parent_child);
	pthread_mutex_unlock(&scheduler->mutex_parent_child);

	// wait to be scheduled
	pthread_mutex_lock(&scheduler->mutex_running);
	if (first) {
		scheduler->current_thread = pair.index;
		scheduler->threads[pair.index].current_time_quantum = scheduler->time_quantum;
		scheduler->threads[pair.index].state = RUNNING;
	}

	/*
	///////////////////////
	*/
	int ind = scheduler->current_thread;
	/*
	//////////////
	*/
	while (scheduler->threads[pair.index].state != RUNNING) {
		printf("Eu ind = %d astepr RUNNING.\n", ind);
		pthread_cond_wait(&scheduler->cond_running,
			&scheduler->mutex_running);
	}

	pair = remove_head(scheduler->ready_queue);
	add(scheduler->ready_queue, pair);

	/*TODO OBS: El o sa fie blocat in alte functii 
	pentru ca voi face wait la inceputul functiilor 
	ca starea lui sa devina RUNNING */
	handler(pair.priority);

	pair = remove_head(scheduler->ready_queue);
	scheduler->threads[pair.index].state = TERMINATED;

	// get another thread
	if (head(scheduler->ready_queue)) {
		printf("[THREAD_FUNCTION]: aproape m-am terminat %d\n", ind);
		printf("[THREAD_FUNCTION]: Dau procesul altuia pentru ca eu m-am terminat.\n");
		pair = remove_head(scheduler->ready_queue);
		scheduler->current_thread = pair.index;
		scheduler->threads[pair.index].state = RUNNING;
		add(scheduler->ready_queue, pair);
		pthread_cond_signal(&scheduler->cond_running);
	}
	pthread_mutex_unlock(&scheduler->mutex_running);
	printf("[THREAD_FUNCTION]: m-am terminat %d\n", ind);
	return NULL;
}

tid_t so_fork(so_handler *func, unsigned int priority)
{
	printf("[SO_SCHEDULER]: Start a new thread, aferent, corespunzator.\n");
	printf("nr_threads = %d\n", scheduler->nr_threads);

	int ret;
	tid_t thread_id;

	if (!func)
		return INVALID_TID;

	scheduler->threads[scheduler->nr_threads].priority = priority;
	scheduler->threads[scheduler->nr_threads].current_time_quantum = scheduler->time_quantum;
	scheduler->threads[scheduler->nr_threads].state = NEW;
	scheduler->threads[scheduler->nr_threads].event = INVALID_EVENT;

	ret = pthread_create(&thread_id, NULL, thread_func, (void *)func);
	if (ret)
		return INVALID_TID;

	// wait
	pthread_mutex_lock(&scheduler->mutex_parent_child);
	// printf("[SO_FORK]: Astept sa fie odrasla programata.\n");
	
	while (scheduler->threads[scheduler->nr_threads].state != READY
		&& scheduler->threads[scheduler->nr_threads].state != RUNNING
		&& scheduler->threads[scheduler->nr_threads].state != TERMINATED) {
		// printf("[SO_FORK]: State: %d\n", scheduler->threads[scheduler->nr_threads].state);
		pthread_cond_wait(&scheduler->cond_parent_child,
			&scheduler->mutex_parent_child);
	}
	
	++scheduler->nr_threads;

	pthread_mutex_unlock(&scheduler->mutex_parent_child);
	// printf("Ma intorc bosilor dupa ce am afacut fork.\n");
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
