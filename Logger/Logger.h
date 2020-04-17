#ifndef LOGGER_H_
#define LOGGER_H_

#define SUCC	0
#define ERR    (-1)

#define MAX_SIZE	200

#define SEEK_SET	0
#define SEEK_END	2

#ifdef __WIN32
#include <windows.h>
#define END_LINE	"\r\n"
#else
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#define END_LINE	"\n"
#endif /* __WIN32 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
#ifdef __WIN32
	HANDLE h;
#else
	int fd;
#endif /* __WIN32 */
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
 * display log file content.
 */
void history(const Logger *const logger);

/*
 * free logger resources.
 */
int destroy_logger(Logger *logger);

#endif /* LOGGER_H_ */
