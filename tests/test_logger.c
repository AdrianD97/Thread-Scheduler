#include <stdio.h>
#include <assert.h>

#ifdef __linux__
#include <unistd.h>

#define SLEEP sleep
#define FACTOR	1
#else
#include <windows.h>

#define SLEEP Sleep
#define FACTOR	1000
#endif /* __linux */

#include "../Logger/Logger.h"

void test_logger(void)
{
	Logger *logger;
	int ret;

	printf("Start test.%s", END_LINE);

	logger = create_logger("file.log");
	assert(logger != NULL);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	SLEEP(1 * FACTOR);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	SLEEP(2 * FACTOR);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	SLEEP(1 * FACTOR);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	SLEEP(2 * FACTOR);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	SLEEP(1 * FACTOR);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = logg(logger, "ls -ld /");
	assert(ret == SUCC);

	ret = logg(logger, "Error1");
	assert(ret == SUCC);

	ret = logg(logger, "Error2");
	assert(ret == SUCC);

	ret = logg(logger, "Error3");
	assert(ret == SUCC);

	ret = logg(logger, "Error4");
	assert(ret == SUCC);

	ret = logg(logger, "Error5");
	assert(ret == SUCC);

	ret = logg(logger, "Error6");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/passwd");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./");
	assert(ret == SUCC);

	ret = logg(logger, "cat /etc/");
	assert(ret == SUCC);

	ret = logg(logger, "ls ./ | head -n 10");
	assert(ret == SUCC);

	ret = destroy_logger(logger);
	assert(ret == SUCC);

	printf("End test.%s", END_LINE);
}

int main(int argc, char const *argv[])
{
	test_logger();

	return 0;
}
