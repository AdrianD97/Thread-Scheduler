#include "so_scheduler.h"
#include "utils/utils.h"

/*
 * referinta catre componenta de tip planificator
 */
static scheduler_t *sch;

int so_init(unsigned int time_quantum, unsigned int io)
{
#ifdef __linux__
	int ret1, ret2;
#endif /* __linux__ */

	if (sch)
		return ERROR_;

	if (!time_quantum || (io > SO_MAX_NUM_EVENTS))
		return ERROR_;

	sch = (scheduler_t *)malloc(sizeof(scheduler_t));
	if (!sch)
		return ERROR_;

	sch->nr_threads = sch->timestamp = 0;
	sch->t_qu = time_quantum;
	sch->nr_events = io;
	sch->state = NOT_YET;

	sch->threads = (thread_t *)malloc(MAX_THREADS * sizeof(thread_t));
	if (!sch->threads) {
		free(sch);
		sch = NULL;
		return ERROR_;
	}

	sch->ready_q = createPriorityQueue(MAX_THREADS);
	if (!sch->ready_q) {
		free(sch->threads);
		free(sch);
		sch = NULL;
		return ERROR_;
	}

#ifdef __linux__
	ret1 = pthread_cond_init(&sch->cond_running, NULL);
	ret2 = pthread_cond_init(&sch->cond_end, NULL);
	if (ret1 | ret2) {
		destroy(sch->ready_q);
		free(sch->ready_q);
		free(sch->threads);

		if (ret1 && !ret2)
			pthread_cond_destroy(&sch->cond_end);
		if (ret2 && !ret1)
			pthread_cond_destroy(&sch->cond_running);

		free(sch);
		sch = NULL;
		return ERROR_;
	}

	ret1 = pthread_mutex_init(&sch->mutex_running, NULL);
	ret2 = pthread_mutex_init(&sch->mutex_end, NULL);
	if (ret1 | ret2) {
		destroy(sch->ready_q);
		free(sch->ready_q);
		free(sch->threads);
		pthread_cond_destroy(&sch->cond_running);
		pthread_cond_destroy(&sch->cond_end);

		if (ret1 && !ret2)
			DESTROY_LOCK(&sch->mutex_end);
		if (ret2 && !ret1)
			DESTROY_LOCK(&sch->mutex_running);
		free(sch);
		sch = NULL;
		return ERROR_;
	}
#else
	InitializeConditionVariable(&sch->cond_running);
	InitializeConditionVariable(&sch->cond_end);

	InitializeCriticalSection(&sch->mutex_running);
	InitializeCriticalSection(&sch->mutex_end);
#endif /* __linux__ */

	return SUCCESS;
}

/*
 * blocheaza executia unui thread din sistem
 * pana cand starea lui devine din nou RUNNING.
 */
static void block(unsigned int index)
{
	BROADCAST(&sch->cond_running);

	while (sch->threads[index].state != RUNNING)
#ifdef __linux__
		WAIT(&sch->cond_running,
			&sch->mutex_running);
#else
		WAIT(&sch->cond_running,
			&sch->mutex_running, INFINITE);
#endif /* __linux__ */
}

/*
 * preempteaza thread-ul curent deoarece i-a expirat
 * cuanta de timp, a fost introdus un thread cu o
 * prioritate mai mare sau a fost trezit un thread
 * cu o prioritate mai mare. Marcheaza thread-ul
 * curent ca fiind in starea READY, iar noul thread
 * va fi marcat ca fiind in starea RUNNING.
 */
static void preempt_crt_thread(unsigned int crt_ind,
	Node *node, unsigned int new_index)
{
	node->timestamp = sch->timestamp++;
	add(sch->ready_q, *node);

	sch->threads[crt_ind].state = READY;
	sch->threads[crt_ind].c_t_qu = sch->t_qu;

	sch->threads[new_index].c_t_qu = sch->t_qu;
	sch->threads[new_index].state = RUNNING;

	block(crt_ind);
}

#ifdef __linux__
static void *thread_func(void *arg)
#else
static DWORD WINAPI thread_func(LPVOID arg)
#endif /* __linux__ */
{
	Node node;
	Node const *pr;
	th_func_arg_t arg_th_func;

	arg_th_func = *(th_func_arg_t *)arg;
	free(arg);
	node = arg_th_func.node;

	LOCK(&sch->mutex_running);
	while (sch->threads[node.index].state != RUNNING)
#ifdef __linux__
		WAIT(&sch->cond_running,
			&sch->mutex_running);
#else
		WAIT(&sch->cond_running,
			&sch->mutex_running, INFINITE);
#endif /* __linux__ */

	arg_th_func.func(node.priority);

	node = remove_head(sch->ready_q);
	sch->threads[node.index].state = TERMINATED;

	pr = head(sch->ready_q);
	if (pr) {
		sch->threads[pr->index].state = RUNNING;
		BROADCAST(&sch->cond_running);
	} else {
		LOCK(&sch->mutex_end);
		sch->state = END;
		SIGNAL(&sch->cond_end);
		UNLOCK(&sch->mutex_end);
	}
	UNLOCK(&sch->mutex_running);

	return RET_VAL;
}

tid_t so_fork(so_handler *func, unsigned int priority)
{
#ifdef __linux__
	int ret;
#else
	HANDLE handle;
#endif /* __linux__ */
	tid_t thread_id;
	Node node, preempt;
	Node const *pr;
	th_func_arg_t *arg;
	int preempted, q, err_flag = 0;
	unsigned int th_ind, index;

	preempted = 0;

	if (!func || (priority > SO_MAX_PRIO))
		return INVALID_TID;

	arg = (th_func_arg_t *)malloc(sizeof(th_func_arg_t));
	if (!arg)
		return INVALID_TID;

	arg->func = func;

	if (sch->state == NOT_YET)
		LOCK(&sch->mutex_running);
	else {
		pr = head(sch->ready_q);
		if (!pr) {
			free(arg);
			return INVALID_TID;
		}

		th_ind = pr->index;
	}

	node.index = sch->nr_threads++;
	node.priority = priority;
	node.timestamp = sch->timestamp++;
	arg->node = node;

	sch->threads[node.index].priority = priority;
	sch->threads[node.index].c_t_qu = sch->t_qu;
	sch->threads[node.index].state = NEW;
	sch->threads[node.index].event = INVALID_EVENT;

	sch->threads[node.index].state = READY;
	add(sch->ready_q, node);

#ifdef __linux__
	ret = pthread_create(&thread_id, NULL, thread_func, (void *)arg);
	if (ret)
		err_flag = 1;
#else
	handle = CreateThread(
		NULL,
		0,
		thread_func,
		arg,
		0,
		&thread_id
	);
	if (handle == NULL)
		err_flag = 1;
#endif /* __linux__ */

	if (err_flag) {
		if (sch->state == NOT_YET)
			UNLOCK(&sch->mutex_running);
		free(arg);
		return INVALID_TID;
	}

#ifdef __linux__
	sch->threads[node.index].thread_id = thread_id;
#else
	sch->threads[node.index].thread_id = handle;
#endif /* __linux__ */

	if (sch->state != NOT_YET) {
		if (node.priority > sch->threads[th_ind].priority) {
			preempted = 1;
			index = node.index;
		} else {
			q = --sch->threads[th_ind].c_t_qu;
			if (q == 0) {
				preempt = remove_head(sch->ready_q);
				pr = head(sch->ready_q);
				if (pr) {
					if (pr->priority >= preempt.priority) {
						preempted = 1;
						index = pr->index;
					}
				}

				if (!preempted)
					sch->threads[th_ind].c_t_qu = sch->t_qu;
				add(sch->ready_q, preempt);
			}
		}

		if (preempted) {
			preempt = remove_head(sch->ready_q);
			preempt_crt_thread(th_ind, &preempt, index);
		}
	} else
		sch->threads[node.index].state = RUNNING;

	if (sch->state == NOT_YET) {
		sch->state = START;
		UNLOCK(&sch->mutex_running);
	}

	return thread_id;
}

void so_exec(void)
{
	int th_ind, q;
	unsigned int preempted = 0;
	Node preempt;
	Node const *pr;

	pr = head(sch->ready_q);
	if (!pr)
		return;

	th_ind = pr->index;

	q = --sch->threads[th_ind].c_t_qu;
	if (q == 0) {
		preempt = remove_head(sch->ready_q);
		pr = head(sch->ready_q);
		if (pr) {
			if (pr->priority >= preempt.priority)
				preempted = 1;
		}

		if (!preempted)
			sch->threads[th_ind].c_t_qu = sch->t_qu;
		add(sch->ready_q, preempt);
	}

	if (preempted) {
		preempt = remove_head(sch->ready_q);
		preempt_crt_thread(th_ind, &preempt, pr->index);
	}
}

int so_wait(unsigned int io)
{
	int th_ind;
	Node pr_wait;
	Node const *pr;

	if (io >= sch->nr_events)
		return ERROR_;

	pr_wait = remove_head(sch->ready_q);
	th_ind = pr_wait.index;

	pr = head(sch->ready_q);
	if (pr) {
		sch->threads[pr->index].c_t_qu = sch->t_qu;
		sch->threads[pr->index].state = RUNNING;
	}
	sch->threads[th_ind].c_t_qu = sch->t_qu;
	sch->threads[th_ind].state = WAITING;
	sch->threads[th_ind].event = io;

	block(th_ind);

	return SUCCESS;
}

/*
 * Marcheaza un thread, care a fost in starea
 * WAITING si care a fost trezit de un apel
 * so_signal, ca fiind in starea READY.
 */
static void change(unsigned int th_ind)
{
	Node node;

	node.index = th_ind;
	node.priority = sch->threads[th_ind].priority;
	node.timestamp = sch->timestamp++;
	sch->threads[th_ind].state = READY;
	sch->threads[th_ind].event = INVALID_EVENT;

	add(sch->ready_q, node);
}

/*
 * Marcheaza thread-urile care erau blocate la evenimentul
 * 'event' ca fiind deblocate(deci le adauga in coada
 * READY).
 */
static unsigned int wake_up(unsigned int event)
{
	int left, right;
	unsigned int nr_wake_up_threads = 0;

	left = 0;
	right = sch->nr_threads - 1;
	while (left < right) {
		if (sch->threads[left].state == WAITING
			&& sch->threads[left].event == event) {
			++nr_wake_up_threads;
			change(left);
		}

		if (sch->threads[right].state == WAITING
			&& sch->threads[right].event == event) {
			++nr_wake_up_threads;
			change(right);
		}

		++left;
		--right;
	}

	if (left == right && sch->threads[right].state == WAITING
		&& sch->threads[right].event == event) {
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
	unsigned int th_ind;

	preempted = 0;
	if (io >= sch->nr_events)
		return ERROR_;

	node = remove_head(sch->ready_q);
	th_ind = node.index;
	nr_wake_up_threads = wake_up(io);

	pr = head(sch->ready_q);
	if (pr) {
		if (pr->priority > sch->threads[th_ind].priority)
			preempted = 1;
	}

	q = --sch->threads[th_ind].c_t_qu;
	if (!preempted && (q == 0)) {
		if (pr && pr->priority == sch->threads[th_ind].priority)
			preempted = 1;

		if (!preempted)
			sch->threads[th_ind].c_t_qu = sch->t_qu;
	}

	if (preempted)
		preempt_crt_thread(th_ind, &node, pr->index);
	else
		add(sch->ready_q, node);

	return nr_wake_up_threads;
}

void so_end(void)
{
	unsigned int i;

	if (!sch)
		return;

	LOCK(&sch->mutex_end);
	while (sch->nr_threads && sch->state != END)
#ifdef __linux__
		WAIT(&sch->cond_end, &sch->mutex_end);
#else
		WAIT(&sch->cond_end, &sch->mutex_end, INFINITE);
#endif /* __linux__ */
	UNLOCK(&sch->mutex_end);

	SLEEP(TIME);

	for (i = 0; i < sch->nr_threads; ++i)
#ifdef __linux__
		pthread_join(sch->threads[i].thread_id, NULL);
#else
		CloseHandle(sch->threads[i].thread_id);
#endif /* __linux__ */

	destroy(sch->ready_q);
	free(sch->ready_q);
	free(sch->threads);
#ifdef __linux__
	pthread_cond_destroy(&sch->cond_running);
	pthread_cond_destroy(&sch->cond_end);
#endif
	DESTROY_LOCK(&sch->mutex_running);
	DESTROY_LOCK(&sch->mutex_end);

	free(sch);
	sch = NULL;
}
