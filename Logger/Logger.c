#include "Logger.h"

/*
 * Ar trebui sa setez o limita pentru contor
 * Gen mai trbuie sa iau un parametru care sa imi spuna cate
 * intrari am pus
 * iar in momentul in care numarul de intraria atins o limita
 * maxima definita
 * va trebui sa sterg de la inceput o linie si sa adaug la sfarsit
 * noua linie venita

 * TODO: Alt feature ar fi cand dau clear la history sa
 * golsec fisierul si sa dau
 * contorului valoarea primei linii din fisierul pe
 * care il voi goli.
 * Deci as putea avea inca o variabila care retine tot
 * timpul id-ul data primei linii
 * Aceasta se va modifica, cand numarul de intrari se va
 * atinge, voi setrge prima linie
 * iar variabila va lua valorea +1(adica pt urmatoare linie
 * care devine prima)
 * iar cand dau clear sa devina variabila + 1, iar
 * contor o sa inceapa de la variabila + 1
 * MAI VEDEM DACA IMPLEMENTAM SI Aceasta
 */
/*
 *TODO TODO  TODO: Voi aplica solutia cu stergere
 * fisier/golire fisier cand am atins numarul amxim
 * de intarri. :)))
 */
Logger *create_logger(char *file_name)
{
	Logger *logger;
	int err_flag = 0;

	logger = (Logger *)malloc(sizeof(Logger));
	if (!logger)
		return NULL;

#ifdef __linux__
	logger->fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC);
	if (logger->fd < 0)
		err_flag = 1;
#else
	logger->h = CreateFile(
		(LPCSTR)file_name,
		GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (logger->h == INVALID_HANDLE_VALUE)
		err_flag = 1;
#endif /* __linux__ */

	if (err_flag) {
		free(logger);
		return NULL;
	}

	logger->contor = 1;
	return logger;
}

int logg(Logger *const logger, char *message)
{
#ifdef _WIN32
	BOOL ret;
#endif /* _WIN32 */

	char final_message[MAX_SIZE];
	int length;
	int index, bytes_written;
	time_t ts;
	struct tm *t;

	if (!message)
		return -ERR;

	/*
	 * TODO: Sa adaug si data si ora curenta in mesaj
	 */
	ts = time(NULL);
	t = gmtime((const time_t *)&ts);
	sprintf(final_message, "%d\t%d-%d-%d %d:%d:%d\t%s%s",
		logger->contor, t->tm_mday, t->tm_mon,
		1900 + t->tm_year, t->tm_hour, t->tm_min,
		t->tm_sec, message, END_LINE);
	++logger->contor;
	length = strlen(final_message);
	index = 0;

	while (length > 0) {
#ifdef __linux__
		bytes_written = write(logger->fd,
			&final_message[index], length);

		if (bytes_written < 0)
			return -ERR;
#else
		ret = WriteFile(
			logger->h,
		    &final_message[index],
		    length,
		    &bytes_written,
		    NULL
		);

		if (ret == FALSE)
			return -ERR;
#endif /* __linux__ */

		index += bytes_written;
		length -= bytes_written;
	}

	return SUCC;
}

int destroy_logger(Logger *logger)
{
#ifdef _WIN32
	BOOL rc;
#endif /* __WIN32 */
	int ret;

	if (!logger)
		return -ERR;

#ifdef __linux__
	ret = close(logger->fd);
#else
	rc = CloseHandle(logger->h);
	ret = (rc == FALSE) ? -ERR : SUCC;
#endif /* __linux__ */

	free(logger);

	return ret;
}
