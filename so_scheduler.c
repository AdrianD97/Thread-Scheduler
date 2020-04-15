/* TODO: Only testing ppurpose */
#include <stdio.h>
/* TODO: End of testing code */

#include "so_scheduler.h"
#include "utils/utils.h"

static scheduler_t *scheduler;

pthread_mutexattr_t attr;

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

static STATE get_current_thread_id(tid_t thread_id)
{
	unsigned int i;

	for (i = 0; i < scheduler->nr_threads; ++i) {
		if (scheduler->threads[i].thread_id == thread_id) {
			return i;
		}
	}

	return INVALID_INDEX;
}

static void* thread_func(void *arg)
{
	Node node;
	Node const *pr;
	th_func_arg arg_th_func;

	arg_th_func = *(th_func_arg *)arg;
	node = arg_th_func.node;

	scheduler->threads[node.index].thread_id = pthread_self();

	// printf("Thread %d stau si astept pt ca sunt prost.\n", node.index);
	pthread_mutex_lock(&scheduler->mutex_running);
	while (scheduler->threads[node.index].state != RUNNING) {
		/*Ar trenui blocat thread-ul curent si deblocat thread-ul care sta aici*/
		// printf("Thread %d astept la running. -> state = %d\n", node.index, scheduler->threads[node.index].state);
		pthread_cond_wait(&scheduler->cond_running, &scheduler->mutex_running);
	}
	// printf("Thread %d am trecut de wait, merg la handler.\n", node.index);

	arg_th_func.func(node.priority);
	if (scheduler->threads[node.index].preempted == PREEMPTED) {
		pthread_mutex_lock(&scheduler->mutex_running);
		while (scheduler->threads[node.index].state != RUNNING) {
			pthread_cond_wait(&scheduler->cond_running, &scheduler->mutex_running);
		}
		// scheduler->threads[node.index].preempted = NO_PREEMPTED;
		// pthread_mutex_lock(&scheduler->mutex_running);
		// printf("Am luat eu mutexyugengjrkgrgnhr rjkhrjt\n");
	}
	/* sa verific daca cumva a fost preemptat si sa pun aiar mana pe lock ??
	asta insemana ca mai trebuie un camp in structura thread_t */
	node = remove_head(scheduler->ready_queue);
	scheduler->threads[node.index].state = TERMINATED;

	pr = head(scheduler->ready_queue);
	if (pr) {
		//========================
		// printf("Thread %d zice ca avem: ", node.index);
		// for (int i = 1; i <= scheduler->ready_queue->index; ++i) {
		// 	printf("(ind, prio, time)=(%d, %d, %d) ", scheduler->ready_queue->arr[i].index,
		// 		scheduler->ready_queue->arr[i].priority,
		// 		scheduler->ready_queue->arr[i].timestamp);
		// }
		// printf("\n, next is %d\n", pr->index);
		//========================
		scheduler->current_thread = pr->index;
		scheduler->threads[pr->index].state = RUNNING;
		pthread_cond_broadcast(&scheduler->cond_running);
	}
	// else {
	// 	printf("Nu am nimic in ready_queue. HA, HA, HA\n");
	// }

	pthread_mutex_unlock(&scheduler->mutex_running);

	return NULL;
}

tid_t so_fork(so_handler *func, unsigned int priority)
{
	int ret, nr_th, q, nr;
	tid_t thread_id;
	Node node, pr_preempted;
	Node const *pr;
	th_func_arg arg;
	int preempted, from_queue;
	unsigned int thread_index;

	preempted = from_queue = 0;

	if (!func)
		return INVALID_TID;

	arg.func = func;
	/* cred ca pot s am folosesc tot de scheduler->current_thread, de fapt nope */
	pthread_mutex_lock(&scheduler->mutex_running);
	if (scheduler->current_thread != INVALID_INDEX) {
		thread_index = get_current_thread_id(pthread_self());
	}
	/* Trebuie sa astept daca am fost preemptat la o instructiune anterioara */
	if (scheduler->current_thread != INVALID_INDEX) {
		while (scheduler->threads[thread_index].state != RUNNING) {
			pthread_cond_wait(&scheduler->cond_running, &scheduler->mutex_running);
		}
	}

	nr_th = scheduler->nr_threads++;
	scheduler->threads[nr_th].priority = priority;
	scheduler->threads[nr_th].current_time_quantum = scheduler->time_quantum;
	scheduler->threads[nr_th].state = NEW;
	scheduler->threads[nr_th].event = INVALID_EVENT;
	scheduler->threads[nr_th].preempted = NO_PREEMPTED;
	node.priority = priority;
	node.timestamp = scheduler->timestamp++;
	node.index = nr_th;
	arg.node = node;
	////////////////////////////////////////////////
	scheduler->threads[node.index].state = READY;
	add(scheduler->ready_queue, node);
	//////////////////////////////////////////////////

	ret = pthread_create(&thread_id, NULL, thread_func, (void *)&arg);
	if (ret)
		return INVALID_TID;

	///////////////////////////////////////////////////////
	if (scheduler->current_thread != INVALID_INDEX) {
		if (node.priority > scheduler->threads[scheduler->current_thread].priority)
			preempted = 1;
		else {
			q = --scheduler->threads[scheduler->current_thread].current_time_quantum;
			if (q == 0) {
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
		////////////////////////////////////////////
		if (preempted) {
			scheduler->threads[thread_index].preempted = PREEMPTED;
			printf("Thread %d am fost preempted.\n", scheduler->current_thread);
			pr_preempted = remove_head(scheduler->ready_queue);
			pr_preempted.timestamp = scheduler->timestamp++;
			add(scheduler->ready_queue, pr_preempted);

			nr = scheduler->current_thread;
			scheduler->threads[scheduler->current_thread].state = READY;
			scheduler->threads[scheduler->current_thread].current_time_quantum = scheduler->time_quantum;
			if (from_queue) {
				scheduler->current_thread = pr->index;
				scheduler->threads[pr->index].current_time_quantum = scheduler->time_quantum;
				scheduler->threads[pr->index].state = RUNNING;
				/* TODO: Wrong, wrong, wrong deoarece noi suntem in contextul unui
				thread(de exemplu aici este thread 2)*/
			} else {
				scheduler->current_thread = node.index;
				scheduler->threads[node.index].current_time_quantum = scheduler->time_quantum;
				scheduler->threads[node.index].state = RUNNING;
			}
			pthread_cond_broadcast(&scheduler->cond_running);
			pthread_mutex_unlock(&scheduler->mutex_running);
		}
		////////////////////////////////////////////
	} else {
		scheduler->current_thread = node.index;
		scheduler->threads[node.index].state = RUNNING;
	}

	// daca sunt preemptat va trebui sa sa astept la urmatorul apel so_fork

	////////////////////////////////////////////////////

	// if (scheduler->current_thread != INVALID_INDEX && 
	// 	scheduler->threads[thread_index].preempted) {
	// 	scheduler->threads[thread_index].preempted = NO_PREEMPTED;
	// 	pthread_mutex_lock(&scheduler->mutex_running);
	// }
	pthread_mutex_unlock(&scheduler->mutex_running);

	return thread_id;
}

void so_end(void)
{
	// printf("[SO_SCHEDULER]: Fac si eu o dezalocare corespunzatoare.\n");
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
