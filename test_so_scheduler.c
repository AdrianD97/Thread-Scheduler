#include <stdio.h>
#include <limits.h>
#include "so_scheduler.h"


void func(unsigned int p)
{

}

void func_(unsigned int p)
{
	tid_t t_id = so_fork(&func, 140);

	printf("[FUNC_]: Primul apel a lui so_fork a intors: %lu\n", t_id);

	t_id = so_fork(&func, 10);

	printf("[FUNC_]: Al doilea apel a lui so_fork a intors: %lu\n", t_id);

	t_id = so_fork(&func, 14);

	printf("[FUNC_]: Al treilea apel a lui so_fork a intors: %lu\n", t_id);

	t_id = so_fork(&func, 0);

	printf("[FUNC_]: Al patrulea apel a lui so_fork a intors: %lu\n", t_id);

	t_id = so_fork(&func, 10);

	printf("[FUNC_]: Al cincilea apel a lui so_fork a intors: %lu\n", t_id);

	t_id = so_fork(&func, 1);

	printf("[FUNC_]: Al saselea apel a lui so_fork a intors: %lu\n", t_id);

	t_id = so_fork(&func, 7);

	printf("[FUNC_]: Al saptelea apel a lui so_fork a intors: %lu\n", t_id);

}

void f2(unsigned int p)
{
	tid_t t_id = so_fork(&func_, 10);

	printf("[F2]: primul apel al lui so_fork a intors %lu\n", t_id);

	t_id = so_fork(&func, 10);

	printf("[F2]: al doilea apel al lui so_fork a intors %lu\n", t_id);

	t_id = so_fork(&func, 0);

	printf("[F2]: al treilea apel al lui so_fork a intors %lu\n", t_id);

	t_id = so_fork(&func, 10);

	printf("[F2]: al patrulea apel al lui so_fork a intors %lu\n", t_id);

	t_id = so_fork(&func, 30);

	printf("[F2]: al cincilea apel al lui so_fork a intors %lu\n", t_id);

	t_id = so_fork(&func, 10);

	printf("[F2]: al saptelea apel al lui so_fork a intors %lu\n", t_id);

	t_id = so_fork(&func, 200);

	printf("[F2]: al saptelea apel al lui so_fork a intors %lu\n", t_id);
}

void f1(unsigned int p)
{
	tid_t t_id = so_fork(&func_, 10);

	printf("[F1]: primul apel al lui so_fork a intors %lu\n", t_id);

	t_id = so_fork(&func_, 100);

	printf("[F1]: al doilea apel al lui so_fork a intors %lu\n", t_id);

	t_id = so_fork(&func_, 10);

	printf("[F1]: al treilea apel al lui so_fork a intors %lu\n", t_id);

	t_id = so_fork(&f2, 10);

	printf("[F1]: al patrulea apel al lui so_fork a intors %lu\n", t_id);

}

int main(int argc, char const *argv[])
{
	unsigned int q = 2;
	unsigned int io = 20;

	so_init(q, io);

	tid_t t_id = so_fork(&f1, 10);

	printf("[MAIN]: Apelul de so_fork a intors: %lu\n", t_id);

	so_end();
	return 0;
}