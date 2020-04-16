/* TODO: Only testing ppurpose */
#include <stdio.h>
/* TODO: End of testing code */

#include "so_scheduler.h"
#include "utils/utils.h"

static scheduler_t *scheduler;

static pthread_mutexattr_t attr;

int so_init(unsigned int time_quantum, unsigned int io)
{
	int ret1, ret2;

	if (io >= SO_MAX_NUM_EVENTS)
		return ERROR;

	scheduler = (scheduler_t *)malloc(sizeof(scheduler_t));
	if (!scheduler)
		return ERROR;

	scheduler->nr_threads = scheduler->timestamp = 0;
	scheduler->time_quantum = time_quantum;
	scheduler->nr_events = io;
	scheduler->state = NOT_YET;
	
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
	ret2 = pthread_cond_init(&scheduler->cond_end, NULL);
	if (ret1 | ret2) {
		destroy(scheduler->ready_queue);
		free(scheduler->ready_queue);
		free(scheduler->threads);

		if (ret1 && !ret2)
			pthread_cond_destroy(&scheduler->cond_end);
		if (ret2 && !ret1)
			pthread_cond_destroy(&scheduler->cond_running);

		free(scheduler);
		return ERROR;
	}

	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	ret1 = pthread_mutex_init(&scheduler->mutex_running, &attr);
	pthread_mutex_init(&scheduler->mutex_end, NULL);
	if (ret1 | ret2) {
		destroy(scheduler->ready_queue);
		free(scheduler->ready_queue);
		free(scheduler->threads);
		pthread_cond_destroy(&scheduler->cond_running);
		pthread_cond_destroy(&scheduler->cond_end);

		if (ret1 && !ret2)
			pthread_mutex_destroy(&scheduler->mutex_end);
		if (ret2 && !ret1)
			pthread_mutex_destroy(&scheduler->mutex_running);
		free(scheduler);
		return ERROR;
	}

	return SUCCESS;
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
		// printf("Thred %d zice ca next is %d.\n", node.index, pr->index);
		scheduler->threads[pr->index].state = RUNNING;
		pthread_cond_broadcast(&scheduler->cond_running);
	} else {
		pthread_mutex_lock(&scheduler->mutex_end);
		scheduler->state = END;
		pthread_cond_broadcast(&scheduler->cond_end);
		pthread_mutex_unlock(&scheduler->mutex_end);
	}
	printf("Thred %d m-am terminat.\n", node.index);
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

	if (!func || (priority > SO_MAX_PRIO))
		return INVALID_TID;

	arg = (th_func_arg *)malloc(sizeof(th_func_arg));
	if (!arg)
		return INVALID_TID;

	arg->func = func;

	pthread_mutex_lock(&scheduler->mutex_running);
	if (scheduler->state != NOT_YET) {
		pr = head(scheduler->ready_queue);
		if (!pr) {
			pthread_mutex_unlock(&scheduler->mutex_running);
			return INVALID_TID;
		}
		thread_index = pr->index;
		printf("Thred %d face so_fork.\n", thread_index);
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
	if (ret) {
		pthread_mutex_unlock(&scheduler->mutex_running);
		return INVALID_TID;
	}

	if (scheduler->state != NOT_YET) {
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
			pr_preempted = remove_head(scheduler->ready_queue);
			pr_preempted.timestamp = scheduler->timestamp++;
			add(scheduler->ready_queue, pr_preempted);

			scheduler->threads[thread_index].state = READY;
			scheduler->threads[thread_index].current_time_quantum = scheduler->time_quantum;

			scheduler->threads[index].current_time_quantum = scheduler->time_quantum;
			scheduler->threads[index].state = RUNNING;

			pthread_cond_broadcast(&scheduler->cond_running);
			if (scheduler->threads[thread_index].preempted == NO_PREEMPTED) {
				scheduler->threads[thread_index].preempted = PREEMPTED;
				pthread_mutex_unlock(&scheduler->mutex_running);
			}

			while (scheduler->threads[thread_index].state != RUNNING) {
				// printf("[SO_FORK]: Thred %d stau in so_fork si astept pt ca %d este acum.\n",
					// thread_index, index);
				pthread_cond_wait(&scheduler->cond_running, &scheduler->mutex_running);
			}
		}
	} else {
		scheduler->state = START;
		scheduler->threads[node.index].state = RUNNING;
	}

	pthread_mutex_unlock(&scheduler->mutex_running);

	return thread_id;
}

void so_exec(void)
{
	int thread_index, q;
	unsigned int preempted = 0;
	Node pr_preempted;
	Node const *pr;

	pthread_mutex_lock(&scheduler->mutex_running);
	pr = head(scheduler->ready_queue);
	if (!pr) {
		pthread_mutex_unlock(&scheduler->mutex_running);
		return;
	}
	thread_index = pr->index;
	printf("Thred %d face so_exec.\n", thread_index);

	q = --scheduler->threads[thread_index].current_time_quantum;
	if (q == 0) {
		// printf("Thred %d mi-a expireat cuanta\n", thread_index);
		pr_preempted = remove_head(scheduler->ready_queue);
		pr = head(scheduler->ready_queue);
		if (pr) {
			if (pr->priority >= pr_preempted.priority)
				preempted = 1;
		}

		if (!preempted)
			scheduler->threads[thread_index].current_time_quantum = scheduler->time_quantum;
		add(scheduler->ready_queue, pr_preempted);
	}

	if (preempted) {
		pr_preempted = remove_head(scheduler->ready_queue);
		pr_preempted.timestamp = scheduler->timestamp++;
		add(scheduler->ready_queue, pr_preempted);

		scheduler->threads[thread_index].state = READY;
		scheduler->threads[thread_index].current_time_quantum = scheduler->time_quantum;

		scheduler->threads[pr->index].current_time_quantum = scheduler->time_quantum;
		scheduler->threads[pr->index].state = RUNNING;
		// printf("Ma inlocuieste %d\n", pr->index);

		pthread_cond_broadcast(&scheduler->cond_running);
		if (scheduler->threads[thread_index].preempted == NO_PREEMPTED) {
			scheduler->threads[thread_index].preempted = PREEMPTED;
			pthread_mutex_unlock(&scheduler->mutex_running);
		}

		while (scheduler->threads[thread_index].state != RUNNING) {
			// printf("[SO_EXEC]: Thred %d sta si asteapta dupa RUNNING\n", thread_index);
			pthread_cond_wait(&scheduler->cond_running, &scheduler->mutex_running);
		}
	}
	pthread_mutex_unlock(&scheduler->mutex_running);
}

/*
	TODO: Avem o mica, mai mare problema:
	Nu cred ca va trebui sa se faca wait in functii, si doar schimb
	starea, dar nu cred ca va merge ?? Trebuie sa rumegam un pic asta.

	TODO: Inca o problema, daca operatia a esuat, tot va trebui sa contorizez
	aceasta operatie, pentru ca a fost facuta sau NU, habar nu am.
	daca iau asta in considerare, atunci va trebui sa pastrez chestiile cu
	verififcare preemptare si sa imi marchez un flag cu ERROARE sau SUCCES si
	voi intoarce flag-ul la sfarsit.
*/
int so_wait(unsigned int io)
{
	int thread_index;
	Node pr_wait;
	Node const *pr;

	pthread_mutex_lock(&scheduler->mutex_running);
	if (io >= scheduler->nr_events) {
		pthread_mutex_unlock(&scheduler->mutex_running);
		return ERROR;
	}

	pr_wait = remove_head(scheduler->ready_queue);
	thread_index = pr_wait.index;
	printf("Thred %d face so_wait.\n", thread_index);

	pr = head(scheduler->ready_queue);
	if (pr) {
		scheduler->threads[pr->index].current_time_quantum = scheduler->time_quantum;
		scheduler->threads[pr->index].state = RUNNING;
	}
	scheduler->threads[thread_index].current_time_quantum = scheduler->time_quantum;
	scheduler->threads[thread_index].state = WAITING;
	scheduler->threads[thread_index].event = io;

	pthread_cond_broadcast(&scheduler->cond_running);
	if (scheduler->threads[thread_index].preempted == NO_PREEMPTED) {
		scheduler->threads[thread_index].preempted = PREEMPTED;
		pthread_mutex_unlock(&scheduler->mutex_running);
	}

	while (scheduler->threads[thread_index].state != RUNNING) {
		// printf("[SO_WAIT]: Thred %d sta si asteapta dupa RUNNING\n", thread_index);
		pthread_cond_wait(&scheduler->cond_running, &scheduler->mutex_running);
	}
	pthread_mutex_unlock(&scheduler->mutex_running);

	return SUCCESS;
}

static void change(unsigned int thread_index)
{
	Node node;

	node.index = thread_index;
	node.priority = scheduler->threads[thread_index].priority;
	node.timestamp = scheduler->timestamp++;
	scheduler->threads[thread_index].state = READY;
	scheduler->threads[thread_index].event = INVALID_EVENT;

	add(scheduler->ready_queue, node);
}

static unsigned int wake_up(unsigned int event)
{
	int left, right;
	unsigned int nr_wake_up_threads = 0;

	left = 0;
	right = scheduler->nr_threads - 1;
	while (left < right) {
		if (scheduler->threads[left].state == WAITING
			&& scheduler->threads[left].event == event) {
			++nr_wake_up_threads;
			change(left);
		}

		if (scheduler->threads[right].state == WAITING
			&& scheduler->threads[right].event == event) {
			++nr_wake_up_threads;
			change(right);
		}

		++left;
		--right;
	}

	if (left == right && scheduler->threads[right].state == WAITING
		&& scheduler->threads[right].event == event) {
		++nr_wake_up_threads;
		change(left);
	}

	return nr_wake_up_threads;
}

int so_signal(unsigned int io)
{
	int nr_wake_up_threads, preempted, q;
	Node node;
	Node const *pr;
	unsigned int thread_index;

	preempted = 0;
	pthread_mutex_lock(&scheduler->mutex_running);
	if (io >= scheduler->nr_events) {
		pthread_mutex_unlock(&scheduler->mutex_running);
		return ERROR;
	}

	node = remove_head(scheduler->ready_queue);
	thread_index = node.index;
	nr_wake_up_threads = wake_up(io);
	printf("Thred %d face so_signal si atrezit %d.\n", thread_index, nr_wake_up_threads);

	pr = head(scheduler->ready_queue);
	if (pr) {
		if (pr->priority > scheduler->threads[thread_index].priority)
			preempted = 1;
	}

	q = --scheduler->threads[thread_index].current_time_quantum;
	if (!preempted && (q == 0)) {
		if (pr && pr->priority == scheduler->threads[thread_index].priority)
			preempted = 1;

		if (!preempted)
			scheduler->threads[thread_index].current_time_quantum = scheduler->time_quantum;
	}

	if (preempted) {
		node.timestamp = scheduler->timestamp++;
		add(scheduler->ready_queue, node);

		scheduler->threads[thread_index].state = READY;
		scheduler->threads[thread_index].current_time_quantum = scheduler->time_quantum;

		scheduler->threads[pr->index].current_time_quantum = scheduler->time_quantum;
		scheduler->threads[pr->index].state = RUNNING;

		pthread_cond_broadcast(&scheduler->cond_running);
		if (scheduler->threads[thread_index].preempted == NO_PREEMPTED) {
			scheduler->threads[thread_index].preempted = PREEMPTED;
			pthread_mutex_unlock(&scheduler->mutex_running);
		}

		while (scheduler->threads[thread_index].state != RUNNING) {
			// printf("[SO_EXEC]: Thred %d sta si asteapta dupa RUNNING\n", thread_index);
			pthread_cond_wait(&scheduler->cond_running, &scheduler->mutex_running);
		}
	} else
		add(scheduler->ready_queue, node);

	pthread_mutex_unlock(&scheduler->mutex_running);

	return nr_wake_up_threads;
}

void so_end(void)
{
	if (!scheduler)
		return;

	pthread_mutex_lock(&scheduler->mutex_end);
	while (scheduler->nr_threads && scheduler->state != END) {
		pthread_cond_wait(&scheduler->cond_end, &scheduler->mutex_end);
	}
	pthread_mutex_unlock(&scheduler->mutex_end);

	for (int i = 0; i < scheduler->nr_threads; ++i) {
		pthread_join(scheduler->threads[i].thread_id, NULL);
	}

	destroy(scheduler->ready_queue);
	free(scheduler->ready_queue);
	free(scheduler->threads);
	pthread_cond_destroy(&scheduler->cond_running);
	pthread_mutex_destroy(&scheduler->mutex_running);
	pthread_cond_destroy(&scheduler->cond_end);
	pthread_mutex_destroy(&scheduler->mutex_end);

	free(scheduler);
	scheduler = NULL;
}
