/* TODO
	doar pentru observatii acest fisier, pentru ca nu stiu daca numele este ok
*/
/*
	1. Am nevoie de un array de obiecte de genul:
		prioritate, stare(enum), cuanta_curenta(va fi initializata cu cuanta initiala
		la fiecare planificare), eveniment dupa care asteapata
*/
#include <stdio.h>
#include "so_scheduler.h"

void func_child_child_child_child_child(unsigned int p)
{

}

void func_child_child_child_child(unsigned int p)
{
	tid_t t_id = so_fork(&func_child_child_child_child_child, 10);

	// printf("Child_child_child_child_child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child_child_child_child, 10);

	// printf("Child_child_child_child_child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child_child_child_child, 20);

	// printf("Child_child_child_child_child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child_child_child_child, 10);

	// printf("Child_child_child_child_child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child_child_child_child, 10);

	// printf("Child_child_child_child_child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child_child_child_child, 10);

	// printf("Child_child_child_child_child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child_child_child_child, 20);

	// printf("Child_child_child_child_child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child_child_child_child, 10);

	// printf("Child_child_child_child_child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child_child_child_child, 10);

	// printf("Child_child_child_child_child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child_child_child_child, 10);

	// printf("Child_child_child_child_child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child_child_child_child, 20);

	// printf("Child_child_child_child_child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child_child_child_child, 101);

	// printf("Child_child_child_child_child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child_child_child_child, 0);

	// printf("Child_child_child_child_child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child_child_child_child, 10);

	// printf("Child_child_child_child_child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child_child_child_child, 203);

	// printf("Child_child_child_child_child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child_child_child_child, 110);

	// printf("Child_child_child_child_child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child_child_child_child, 0);

	// printf("Child_child_child_child_child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child_child_child_child, 110);

	// printf("Child_child_child_child_child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child_child_child_child, 110);

	// printf("Child_child_child_child_child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child_child_child_child, 110);

	// printf("Child_child_child_child_child_child: %lu\n", t_id);
}

void func_child_child_child(unsigned int p)
{
	tid_t t_id = so_fork(&func_child_child_child_child, 10);

	// printf("Child_child_child_child_child: %lu\n", t_id);
}

void func_child_child(unsigned int p)
{
	tid_t t_id = so_fork(&func_child_child_child, 1);

	// printf("Child_child_child_child: %lu\n", t_id);
}

void func_child(unsigned int p)
{
	tid_t t_id = so_fork(&func_child_child, 2);

	// printf("Child_child_child: %lu\n", t_id);
}

void func(unsigned int p)
{
	tid_t t_id = so_fork(&func_child, 1);

	// printf("Child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child, 1);

	// printf("Child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child, 18);

	// printf("Child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child, 1);

	// printf("Child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child, 18);

	// printf("Child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child, 1);

	// printf("Child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child, 18);

	// printf("Child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child, 1);

	// printf("Child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child, 18);

	// printf("Child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child, 1);

	// printf("Child_child: %lu\n", t_id);

	t_id = so_fork(&func_child_child, 18);

	// printf("Child_child: %lu\n", t_id);
}

void func_(unsigned int p)
{
	tid_t t_id = so_fork(&func, 10);

	// printf("Child_child: %lu\n", t_id);

	t_id = so_fork(&func_child, 10);

	// printf("Child_child: %lu\n", t_id);

	t_id = so_fork(&func_child, 1);

	// printf("Child_child: %lu\n", t_id);

	 t_id = so_fork(&func_child, 10);

	// printf("Child_child: %lu\n", t_id);

	t_id = so_fork(&func_child, 109);

	// printf("Child_child: %lu\n", t_id);

	t_id = so_fork(&func_child, 108);

	// printf("Child_child: %lu\n", t_id);
}

int main(int argc, char const *argv[])
{
	unsigned int q = 2;
	unsigned int io = 20;
	// printf("so_init call return %d.\n", so_init(q, io));
	so_init(q, io);

	// tid_t t_id = so_fork(&func, 10);
	tid_t t_id = so_fork(&func_, 10);

	// printf("child: %lu\n", t_id);

	so_end();
	return 0;
}