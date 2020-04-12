/* TODO: Only testing ppurpose */
#include <stdio.h>
/* TODO: End of testing code */

#include "so_scheduler.h"
#include "utils/utils.h"

pthread_mutexattr_t attr;

static scheduler_t *scheduler;

int so_init(unsigned int time_quantum, unsigned int io)
{
	// printf("[SO_SCHEDULER]: Fac si eu o initializare corespunzatoare.\n");
	int ret1, ret2;

	if (io >= SO_MAX_NUM_EVENTS)
		return ERROR;

	scheduler = (scheduler_t *)malloc(sizeof(scheduler_t));
	if (!scheduler)
		return ERROR;

	scheduler->nr_threads = scheduler->timestamp = 0;
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

	Node node, pr_preempted;
	Node const *pr;
	unsigned int q;
	int preempted = 0, first = 0;
	so_handler *handler = (so_handler *)arg;

	pthread_mutex_lock(&scheduler->mutex_parent_child);
	node.index = scheduler->nr_threads++;
	node.timestamp = scheduler->timestamp++;
	// ++scheduler->nr_threads;
	node.priority = scheduler->threads[node.index].priority;

	scheduler->threads[node.index].thread_id = pthread_self();

	scheduler->threads[node.index].state = READY;
	add(scheduler->ready_queue, node);

	int from_queue = 0;
	if (scheduler->current_thread != INVALID_INDEX) {
		q = --scheduler->threads[scheduler->current_thread].current_time_quantum;
		if (node.priority > scheduler->threads[scheduler->current_thread].priority)
			preempted = 1;
		else {
			if (q == 0) { /* Trebuie sa verific si daca nu cumva cel din head are o prioritate mai mica decat a mea
						caz in care nu ma preemptez, sau daca coada este vida*/
				pr_preempted = remove_head(scheduler->ready_queue);
				pr = head(scheduler->ready_queue);
				if (pr) {
					if (pr->priority >= pr_preempted.priority) {
						preempted = 1;
						from_queue = 1;
					}
				}

				if (!preempted)
					scheduler->threads[scheduler->current_thread].current_time_quantum = scheduler->time_quantum;
				add(scheduler->ready_queue, pr_preempted);
			}
		}
	} else
		first = 1;

	if (preempted) {
		printf("[THREAD_FUNCTION]: Thread %d Sa imi bag pl, sunt preemptat ->.\n",
			scheduler->current_thread);
		pr_preempted = remove_head(scheduler->ready_queue);
		pr_preempted.timestamp = scheduler->timestamp++;
		add(scheduler->ready_queue, pr_preempted);
		scheduler->threads[scheduler->current_thread].state = READY;
		scheduler->threads[scheduler->current_thread].current_time_quantum = scheduler->time_quantum;
		if (from_queue) {
			scheduler->current_thread = pr->index;
			scheduler->threads[pr->index].current_time_quantum = scheduler->time_quantum;
			scheduler->threads[pr->index].state = RUNNING;
		} else {
			scheduler->current_thread = node.index;
			scheduler->threads[node.index].current_time_quantum = scheduler->time_quantum;
			scheduler->threads[node.index].state = RUNNING;
		}
	}

	printf("[THREAD_FUNCTION]: Thread %d semanalizez ca am intrat in READY, poate chiar RUNNING.\n",
		node.index);
	pthread_cond_signal(&scheduler->cond_parent_child);
	pthread_mutex_unlock(&scheduler->mutex_parent_child);

	printf("[THREAD_FUNCTION]: Thread %d sunt chiar inainte de mutex mutex_running.\n", node.index);
	// wait to be scheduled
	pthread_mutex_lock(&scheduler->mutex_running);
	printf("[THREAD_FUNCTION]: Thread %d am intrat in mutex mutex_running.\n", node.index);
	if (first) {
		scheduler->current_thread = node.index;
		scheduler->threads[node.index].current_time_quantum = scheduler->time_quantum;
		scheduler->threads[node.index].state = RUNNING;
	}

	/*
	///////////////////////
	*/
	int ind = node.index;
	/*
	//////////////
	*/
	//printf("[THREAD_FUNCTION]: Thread %d ma pregatesc sa astept RUNNING.\n", ind);
	while (scheduler->threads[node.index].state != RUNNING) {
		/* Pun urmatorul apel deoarce:
		sa zicem ca la acesata conditie asteapt 1 ,ia la aceeasi conditie
		dar in so_fork asteapat 5. 6 se termina si spune ca 5 este thread curent.
		6 da semnal, elibereaza mutex, si il ia 1, nu 5. in acest moment 1 se blocheaza din nou,
		5 este inca blocat la conditie in so_fork. deblocheaza mutex-ul. dar nimenil nul va lua.
		5 nu poate sal ia deoarece astepat semnal ca s-a deblocat*/
		// printf("[THREAD_FUNCTION]: Thread %d zice ca avem in heap: ", ind);
		// for (int i = 1; i <= scheduler->ready_queue->index; ++i) {
		// 	printf("(%d, %d) ", scheduler->ready_queue->arr[i].index, scheduler->ready_queue->arr[i].priority);
		// }
		// printf("\n");
		printf("[THREAD_FUNCTION]: Thread %d astept RUNNING.\n", ind);
		// pthread_cond_signal(&scheduler->cond_running);
		pthread_cond_broadcast(&scheduler->cond_running);
		pthread_cond_wait(&scheduler->cond_running,
			&scheduler->mutex_running);
	}

	// node = remove_head(scheduler->ready_queue);
	// add(scheduler->ready_queue, node);

	/*TODO OBS: El o sa fie blocat in alte functii 
	pentru ca voi face wait la inceputul functiilor 
	ca starea lui sa devina RUNNING */
	printf("[THREAD_FUNCTION]: Thread %d apelez imediat handler-furnizat prin arg.\n", ind);
	handler(node.priority);

	node = remove_head(scheduler->ready_queue);
	scheduler->threads[node.index].state = TERMINATED;

	// get another thread
	pr = head(scheduler->ready_queue);
	if (pr) {
		printf("[THREAD_FUNCTION]: Thread %d zice ca avem in heap: ", ind);
		for (int i = 1; i <= scheduler->ready_queue->index; ++i) {
			printf("(%d, %d) ", scheduler->ready_queue->arr[i].index, scheduler->ready_queue->arr[i].priority);
		}
		printf("\n");
		printf("[THREAD_FUNCTION]: Thread %d da procesorul altuia pentru ca eu m-am terminat.\n", ind);
		// //node = remove_head(scheduler->ready_queue);
		printf("[THREAD_FUNCTION]: Thread %d zice ca noul este: %d\n", ind, pr->index);
		// scheduler->current_thread = node.index;
		// scheduler->threads[node.index].state = RUNNING;
		scheduler->current_thread = pr->index;
		scheduler->threads[pr->index].state = RUNNING;
		//printf("[THREAD_FUNCTION]: Thread %d zice ca %d are starea %d.\n", ind, scheduler->current_thread,
			//scheduler->threads[pr->index].state);
		//add(scheduler->ready_queue, node);

		// printf("[THREAD_FUNCTION SECOND ]: Thread %d zice ca avem in heap: ", ind);
		// for (int i = 1; i <= scheduler->ready_queue->index; ++i) {
		// 	printf("(%d, %d) ", scheduler->ready_queue->arr[i].index, scheduler->ready_queue->arr[i].priority);
		// }
		// printf("\n");
		// pthread_cond_signal(&scheduler->cond_running);
		pthread_cond_broadcast(&scheduler->cond_running);
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
	printf("[SO_FORK]: Thread %d l-am luat mutexul mutex_running\n", crt_thread);
	while (crt_thread != INVALID_INDEX &&
		scheduler->threads[crt_thread].state != RUNNING) {
		// printf("Stau si astept pentru ca m-a blocat cineva. -> STATE = %d, crt_thread = %d\n",
			// scheduler->threads[crt_thread].state, crt_thread);
		// Daca wait = 0 ar trebui sa dau unlock, astfel nu
		if (wait == 0) {
			pthread_mutex_unlock(&scheduler->mutex_running);
			wait = 1;
		}
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
