#include <stdio.h>
#include <limits.h>
#include "so_scheduler.h"


void func(unsigned int p)
{
	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

}

void func_(unsigned int p)
{
	so_exec();

	so_exec();
	tid_t t_id = so_fork(&func, 1);

	printf("[FUNC_]: Primul apel a lui so_fork a intors: %lu\n", t_id);

	t_id = so_fork(&func, 1);

	printf("[FUNC_]: Al doilea apel a lui so_fork a intors: %lu\n", t_id);

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	t_id = so_fork(&func, 4);

	printf("[FUNC_]: Al treilea apel a lui so_fork a intors: %lu\n", t_id);

	t_id = so_fork(&func, 0);

	printf("[FUNC_]: Al patrulea apel a lui so_fork a intors: %lu\n", t_id);

	so_exec();

	so_exec();

	t_id = so_fork(&func, 3);

	printf("[FUNC_]: Al cincilea apel a lui so_fork a intors: %lu\n", t_id);

	t_id = so_fork(&func, 1);

	printf("[FUNC_]: Al saselea apel a lui so_fork a intors: %lu\n", t_id);

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	t_id = so_fork(&func, 3);

	printf("[FUNC_]: Al saptelea apel a lui so_fork a intors: %lu\n", t_id);

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	/////
	so_exec();

	so_exec();

	so_exec();

	so_exec();

	t_id = so_fork(&func, 4);

	printf("[FUNC_]: Al treilea apel a lui so_fork a intors: %lu\n", t_id);

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	t_id = so_fork(&func, 0);

	printf("[FUNC_]: Al patrulea apel a lui so_fork a intors: %lu\n", t_id);

	so_exec();

	so_exec();

	t_id = so_fork(&func, 0);

	printf("[FUNC_]: Al cincilea apel a lui so_fork a intors: %lu\n", t_id);

	t_id = so_fork(&func, 1);

	printf("[FUNC_]: Al saselea apel a lui so_fork a intors: %lu\n", t_id);

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	t_id = so_fork(&func, 4);

	printf("[FUNC_]: Al saptelea apel a lui so_fork a intors: %lu\n", t_id);

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	t_id = so_fork(&func, 40);

	printf("[FUNC_]: Al optulea apel a lui so_fork a intors: %lu\n", t_id);

}

void f2(unsigned int p)
{
	tid_t t_id = so_fork(&func_, 0);

	printf("[F2]: primul apel al lui so_fork a intors %lu\n", t_id);

	t_id = so_fork(&func, 1);

	printf("[F2]: al doilea apel al lui so_fork a intors %lu\n", t_id);

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	t_id = so_fork(&func, 0);

	printf("[F2]: al treilea apel al lui so_fork a intors %lu\n", t_id);

	t_id = so_fork(&func, 1);

	printf("[F2]: al patrulea apel al lui so_fork a intors %lu\n", t_id);

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	t_id = so_fork(&func, 0);

	printf("[F2]: al cincilea apel al lui so_fork a intors %lu\n", t_id);

	t_id = so_fork(&func, 1);

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	printf("[F2]: al saselea apel al lui so_fork a intors %lu\n", t_id);

	t_id = so_fork(&func, 2);

	printf("[F2]: al saptelea apel al lui so_fork a intors %lu\n", t_id);
}

void f1(unsigned int p)
{
	tid_t t_id = so_fork(&func_, 2);

	printf("[F1]: primul apel al lui so_fork a intors %lu\n", t_id);

	so_exec();

	so_exec();

	t_id = so_fork(&func_, 2);

	printf("[F1]: al doilea apel al lui so_fork a intors %lu\n", t_id);

	t_id = so_fork(&func_, 5);

	printf("[F1]: al treilea apel al lui so_fork a intors %lu\n", t_id);

	so_exec();

	so_exec();

	t_id = so_fork(&func_, 2);

	printf("[F1]: al doilea apel al lui so_fork a intors %lu\n", t_id);

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	t_id = so_fork(&func_, 2);

	printf("[F1]: al treilea apel al lui so_fork a intors %lu\n", t_id);

	t_id = so_fork(&f2, 0);

	printf("[F1]: al patrulea apel al lui so_fork a intors %lu\n", t_id);

	so_exec();

	so_exec();

	so_exec();

	t_id = so_fork(&func_, 1);

	printf("[F1]: al cincilea apel al lui so_fork a intors %lu\n", t_id);

	t_id = so_fork(&f2, 5);

	printf("[F1]: al saselea apel al lui so_fork a intors %lu\n", t_id);

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

	so_exec();

}

int main(int argc, char const *argv[])
{
	unsigned int q = 2;
	unsigned int io = 20;

	if (so_init(q, io) == -1) {
		printf("ERROR: so_init() failed.\n");
		return -1;
	}

	tid_t t_id = so_fork(&f1, 4);

	printf("[MAIN]: Apelul de so_fork a intors: %lu\n", t_id);

	so_end();
	return 0;
}