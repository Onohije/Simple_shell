#include "ashell.h"

/**
 * freeData - Frees the memory allocated for a data structure.
 *
 * @datash: Data structure
 * Return: No return
 */
void freeData(data_shell *datash)
{
	unsigned int n;

	for (n = 0; datash->_environ[n]; n++)
	{
		free(datash->_environ[n]);
	}

	free(datash->_environ);
	free(datash->pid);
}

/**
 * setData - Initialize data structure.
 *
 * @datash: Data structure.
 * @av: Argument vector.
 * Return: no return.
 */
void setData(data_shell *datash, char **av)
{
	unsigned int n;

	datash->av = av;
	datash->inpt = NULL;
	datash->args = NULL;
	datash->sta = 0;
	datash->contn = 1;

	for (n = 0; environ[n]; n++)
		;

	datash->_environ = malloc(sizeof(char *) * (n + 1));

	for (n = 0; environ[n]; n++)
	{
		datash->_environ[n] = strdup_(environ[n]);
	}

	datash->_environ[n] = NULL;
	datash->pid = auxItoa(getpid());
}

/**
 * main - Entry point.
 *
 * @ac: argument count.
 * @av: argument vector.
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	data_shell datash;
	(void) ac;

	signal(SIGINT, getSigint);
	setData(&datash, av);
	shellLoop(&datash);
	freeData(&datash);
	if (datash.sta < 0)
		return (255);
	return (datash.sta);
}
