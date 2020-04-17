#include <stdio.h>
#include <assert.h>

#include "Logger/Logger.h"

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

	history(logger);

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

	history(logger);

	ret = destroy_logger(logger);
	assert(ret == SUCC);

	printf("End test.%s", END_LINE);
}

int main(int argc, char const *argv[])
{
	test_logger();

	return 0;
}
