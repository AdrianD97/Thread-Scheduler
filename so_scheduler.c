/* TODO: Only testing ppurpose */
#include <stdio.h>
/* TODO: End of testing code */

#include "so_scheduler.h"
#include "utils/utils.h"

static scheduler_t *scheduler;

static pthread_mutexattr_t attr;

int so_init(unsigned int time_quantum, unsigned int io)
{
	int ret;

	if (io >= SO_MAX_NUM_EVENTS)
		return ERROR;

	scheduler = (scheduler_t *)malloc(sizeof(scheduler_t));
	if (!scheduler)
		return ERROR;

	scheduler->nr_threads = scheduler->timestamp = 0;
	scheduler->time_quantum = time_quantum;
	scheduler->nr_events = io;
	scheduler->start = NOT_YET;
	
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

	ret = pthread_cond_init(&scheduler->cond_running, NULL);
	if (ret) {
		destroy(scheduler->ready_queue);
		free(scheduler->ready_queue);
		free(scheduler->threads);
		free(scheduler);
		return ERROR;
	}

	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

	ret = pthread_mutex_init(&scheduler->mutex_running, &attr);

	if (ret) {
		destroy(scheduler->ready_queue);
		free(scheduler->ready_queue);
		free(scheduler->threads);
		pthread_cond_destroy(&scheduler->cond_running);
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
	free(arg);
	node = arg_th_func.node;

	scheduler->threads[node.index].thread_id = pthread_self();

	pthread_mutex_lock(&scheduler->mutex_running);
	while (scheduler->threads[node.index].state != RUNNING) {
		pthread_cond_wait(&scheduler->cond_running, &scheduler->mutex_running);
	}

	arg_th_func.func(node.priority);

	if (scheduler->threads[node.index].preempted == PREEMPTED) {
		pthread_mutex_lock(&scheduler->mutex_running);
		while (scheduler->threads[node.index].state != RUNNING) {
			pthread_cond_wait(&scheduler->cond_running, &scheduler->mutex_running);
		}
		scheduler->threads[node.index].preempted = NO_PREEMPTED;
	}

	node = remove_head(scheduler->ready_queue);
	scheduler->threads[node.index].state = TERMINATED;

	pr = head(scheduler->ready_queue);
	if (pr) {
		scheduler->threads[pr->index].state = RUNNING;
		pthread_cond_broadcast(&scheduler->cond_running);
	}
	pthread_mutex_unlock(&scheduler->mutex_running);

	return NULL;
}

tid_t so_fork(so_handler *func, unsigned int priority)
{
	int ret, q;
	tid_t thread_id;
	Node node, pr_preempted;
	Node const *pr;
	th_func_arg *arg;
	int preempted;
	unsigned int thread_index, index;

	preempted = 0;

	if (!func)
		return INVALID_TID;

	arg = (th_func_arg *)malloc(sizeof(th_func_arg));
	if (!arg) {
		return INVALID_TID;
	}

	arg->func = func;

	pthread_mutex_lock(&scheduler->mutex_running);
	if (scheduler->start != NOT_YET) {
		thread_index = get_current_thread_id(pthread_self());
		if (thread_index == INVALID_INDEX)
			return INVALID_TID;

		while (scheduler->threads[thread_index].state != RUNNING) {
			pthread_cond_wait(&scheduler->cond_running, &scheduler->mutex_running);
		}
	}

	node.index = scheduler->nr_threads++;
	node.priority = priority;
	node.timestamp = scheduler->timestamp++;

	scheduler->threads[node.index].priority = priority;
	scheduler->threads[node.index].current_time_quantum = scheduler->time_quantum;
	scheduler->threads[node.index].state = NEW;
	scheduler->threads[node.index].event = INVALID_EVENT;
	scheduler->threads[node.index].preempted = NO_PREEMPTED;
	scheduler->threads[node.index].state = READY;
	add(scheduler->ready_queue, node);

	arg->node = node;

	ret = pthread_create(&thread_id, NULL, thread_func, (void *)arg);
	if (ret)
		return INVALID_TID;

	if (scheduler->start != NOT_YET) {
		if (node.priority > scheduler->threads[thread_index].priority) {
			preempted = 1;
			index = node.index;
		} else {
			q = --scheduler->threads[thread_index].current_time_quantum;
			if (q == 0) {
				pr_preempted = remove_head(scheduler->ready_queue);
				pr = head(scheduler->ready_queue);
				if (pr) {
					if (pr->priority >= pr_preempted.priority) {
						preempted = 1;
						index = pr->index;
					}
				}

				if (!preempted)
					scheduler->threads[thread_index].current_time_quantum = scheduler->time_quantum;
				add(scheduler->ready_queue, pr_preempted);
			}
		}

		if (preempted) {
			scheduler->threads[thread_index].preempted = PREEMPTED;
			pr_preempted = remove_head(scheduler->ready_queue);
			pr_preempted.timestamp = scheduler->timestamp++;
			add(scheduler->ready_queue, pr_preempted);

			scheduler->threads[thread_index].state = READY;
			scheduler->threads[thread_index].current_time_quantum = scheduler->time_quantum;

			scheduler->threads[index].current_time_quantum = scheduler->time_quantum;
			scheduler->threads[index].state = RUNNING;

			pthread_cond_broadcast(&scheduler->cond_running);
			pthread_mutex_unlock(&scheduler->mutex_running);
		}
	} else {
		scheduler->start = START;
		scheduler->threads[node.index].state = RUNNING;
	}

	pthread_mutex_unlock(&scheduler->mutex_running);

	return thread_id;
}

void so_end(void)
{
	if (!scheduler)
		return;

	for (int i = 0; i < scheduler->nr_threads; ++i) {
		pthread_join(scheduler->threads[i].thread_id, NULL);
	}

	destroy(scheduler->ready_queue);
	free(scheduler->ready_queue);
	free(scheduler->threads);
	pthread_cond_destroy(&scheduler->cond_running);
	pthread_mutex_destroy(&scheduler->mutex_running);
	free(scheduler);
	scheduler = NULL;
}
