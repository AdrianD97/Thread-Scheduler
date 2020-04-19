#include <stdio.h>
#include <stdlib.h>
#include "so_scheduler.h"
#include "../../Logger/Logger.h"

void h3(unsigned int p)
{
	so_exec();

	so_exec();
}

void h1(unsigned int p)
{
	tid_t t_id;

	so_exec();

	printf("[H1]: primul apel a lui so_signal a intors %d\n", so_signal(3));

	t_id = so_fork(&h3, 1);

	printf("[H1]: primul apel al lui so_fork a intors %lu\n", t_id);

	so_exec();

	so_exec();

	so_exec();
}

void h2(unsigned int p)
{
	so_exec();

	printf("[H2]: primul apel a lui so_wait a intors %d\n", so_wait(3));

	so_exec();
}

void h0(unsigned int p)
{
	tid_t t_id;

	so_exec();

	t_id = so_fork(&h2, 2);

	printf("[H0]: primul apel al lui so_fork a intors %lu\n", t_id);

	t_id = so_fork(&h1, 1);

	printf("[H0]: al doilea apel al lui so_fork a intors %lu\n", t_id);

	so_exec();
}

void test_init_params_quantum(void)
{
	printf("%s\n", __func__);
	so_init(0, 0, 1);
	so_end();
}

void test_init_params_io(void)
{
	printf("%s\n", __func__);
	so_init(1, SO_MAX_NUM_EVENTS + 1, 1);
	so_end();
}

void test_init(void)
{
	printf("%s\n", __func__);
	so_init(5, 0, 1);
	so_end();
}

void test_already_exists(void)
{
	printf("%s\n", __func__);
	so_init(5, 0, 1);

	so_init(7, 0, 1);

	so_end();
}

void test_scheduler_with_logger_enabled(void)
{
	unsigned int q = 2;
	unsigned int io = 20;
	tid_t t_id;

	printf("%s\n", __func__);
	if (so_init(q, io, 1) == -1) {
		printf("ERROR: so_init() failed.\n");
		return;
	}

	t_id = so_fork(&h0, 0);

	printf("[TEST_SCHEDULER]: Apelul de so_fork a intors: %lu\n", t_id);

	so_end();
}

void test_scheduler_without_logger_enabled(void)
{
	unsigned int q = 2;
	unsigned int io = 20;
	tid_t t_id;

	printf("%s\n", __func__);
	if (so_init(q, io, 0) == -1) {
		printf("ERROR: so_init() failed.\n");
		return;
	}

	t_id = so_fork(&h0, 0);

	printf("[TEST_SCHEDULER]: Apelul de so_fork a intors: %lu\n", t_id);

	so_end();
}

int main(int argc, char const *argv[])
{
	int test_case;

	if (argc < 2) {
		printf("Error: Invalid number of argumens. ");
		printf("Usage: ./test_so_scheduler test_number\n");
		return -1;
	}

	test_case = atoi(argv[1]);

	switch (test_case) {
	case 0:
		test_init_params_quantum();
		break;
	case 1:
		test_init_params_io();
		break;
	case 2:
		test_init();
		break;
	case 3:
		test_already_exists();
		break;
	case 4:
		test_scheduler_without_logger_enabled();
		break;
	default:
		test_scheduler_with_logger_enabled();
	}

	return 0;
}
