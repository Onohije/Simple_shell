#include "ashell.h"

/**
 * readLine - To reads the input string.
 *
 * @i: Return value of getline function
 * Return: input str
 */
char *readLine(int *i)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i = getline(&input, &bufsize, stdin);

	return (input);
}
