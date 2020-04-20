#ifndef LOGGER_H_
#define LOGGER_H_

#define SUCC	0
#define ERR     1

#define MAX_SIZE	500

#define SEEK_SET	0
#define SEEK_END	2

#ifdef __linux__
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define END_LINE	"\n"
#else
#include <windows.h>

#define END_LINE	"\r\n"
#endif /* __linux__ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * structura ce caracterizeaza componenta de logging.
 */
typedef struct {
#ifdef __linux__
	int fd;
#else
	HANDLE h;
#endif /* __linux__ */
	int contor;
} Logger;

/*
 * init logger.
 * return a pointer to logger object.
 */
Logger *create_logger(char *file_name);

/*
 * write a message to log file.
 */
int logg(Logger *const logger, char *message);

/*
 * free logger resources.
 */
int destroy_logger(Logger *logger);

#endif /* LOGGER_H_ */
