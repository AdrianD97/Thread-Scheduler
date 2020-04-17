#include "Logger.h"

/*
Ar trebui sa setez o limita pentru contor
Gen mai trbuie sa iau un parametru care sa imi spuna cate intrari am pus
iar in momentul in care numarul de intraria atins o limita maxima definita
va trebui sa sterg de la inceput o linie si sa adaug la sfarsit noua linie venita

TODO: Alt feature ar fi cand dau clear la history sa golsec fisierul si sa dau
contorului valoarea primei linii din fisierul pe care il voi goli.
Deci as putea avea inca o variabila care retine tot timpul id-ul data primei linii
Aceasta se va modifica, cand numarul de intrari se va atinge, voi setrge prima linie
iar variabila va lua valorea +1(adica pt urmatoare linie care devine prima)
iar cand dau clear sa devina variabila + 1, iar contor o sa inceapa de la variabila + 1
MAI VEDEM DACA IMPLEMENTAM SI Aceasta
*/
Logger *create_logger(char *file_name)
{
	Logger *logger;
	int err_flag = 0;

	logger = (Logger *)malloc(sizeof(Logger));
	if (!logger)
		return NULL;

#ifdef __WIN32
	logger->h = CreateFile(
		(LPCSTR)file_name,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
#else
	logger->fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC);
	if (logger->fd < 0)
		err_flag = 1;
#endif /* __WIN32 */

	if (err_flag) {
		free(logger);
		return NULL;
	}

	logger->contor = 1;
	return logger;
}

static int set_position(const Logger * const logger,
	int offset, unsigned int whence)
{
#ifdef __WIN32
	DWORD pos;
	pos = SetFilePointer(logger->h, offset,
		NULL, (DWORD)whence);
	if (pos == INVALID_SET_FILE_POINTER)
		return ERR;
#else
	int pos;
	pos = lseek(logger->fd, offset, whence);
	if (pos < 0)
		return ERR;
#endif /* __WIN32 */

	return SUCC;
}

int logg(Logger *const logger, char *message)
{
	if (!message)
		return ERR;

#ifdef __WIN32
	BOOL ret;
#endif /* __WIN32 */

	char final_message[MAX_SIZE];
	int length, res;
	int index, bytes_written;

	sprintf(final_message, "%d\t%s\n", logger->contor, message);
	++logger->contor;
	length = strlen(final_message);
	index = 0;

	res = set_position(logger, 0, SEEK_END);
	if (res == ERR)
		return ERR;

	while (length > 0) {
#ifdef __WIN32
		ret = WriteFile(
			logger->h,
		    &final_message[index],
		    length,
		    &bytes_written,
		    NULL
		);

		if (ret == FALSE)
			return ERR;
#else
		bytes_written = write(logger->fd,
			&final_message[index], length);

		if (bytes_written < 0)
			return ERR;
#endif /* __WIN32 */

		index += bytes_written;
		length -= bytes_written;
	}

	return SUCC;
}

void history(const Logger *const logger)
{
#ifdef __WIN32
	BOOL ret;
#endif /* __WIN32 */

	char buff[MAX_SIZE];
	int bytes_read, res;

	res = set_position(logger, 0, SEEK_SET);
	if (res == ERR)
		return;

	while (1) {
#ifdef __WIN32
		ret = ReadFile(
			logger->h,
		    buff,
			MAX_SIZE,
		    &bytes_read,
		    NULL
		);

		if (ret == FALSE)
			return;
#else
		bytes_read = read(logger->fd, buff, MAX_SIZE);
		if (bytes_read < 0)
			return;
#endif /* __WIN32 */

		if (!bytes_read)
			break;

		buff[bytes_read] = '\0';
		printf("%s", buff);
	}
	printf("\n");
}

int destroy_logger(Logger *logger)
{
	if (!logger)
		return ERR;

	int ret;

#ifdef __WIN32
	BOOL rc = CloseHandle(logger->h);
	ret = (rc == FALSE) ? ERR : SUCC;
#else
	ret = close(logger->fd);
#endif /* __WIN32 */

	free(logger);

	return ret;
}