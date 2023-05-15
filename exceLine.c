#include "ashell.h"

/**
 * execLine - finds builtins and commands
 *
 * @datash: data relevant (args)
 * Return: 1 on success.
 */
int execLine(data_shell *datash)
{
	int (*builtin)(data_shell *datash);

	if (datash->args[0] == NULL)
		return (1);

	builtin = getBuiltin(datash->args[0]);

	if (builtin != NULL)
		return (builtin(datash));

	return (commandExec(datash));
}
