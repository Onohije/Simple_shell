#include "ashell.h"

/**
 * readLine - Reads the input string.
 *
 * @i: Return value of getline function
 * Return: Input str.
 */
char *readLine(int *i)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i = getline(&input, &bufsize, stdin);

	return (input);
}
