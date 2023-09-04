#include "ashell.h"

/**
 * executeLine - To finds builtins and commands
 * @datash: Data relevant to the execution (args)
 * Return: 1 on success.
 */
int executeLine(data_shell *datash)
{
	int (*bull)(data_shell *datash);

	if (datash->args[0] == NULL)
		return (1);

	bull = getBuiltin(datash->args[0]);

	if (bull != NULL)
		return (bull(datash));

	return (commandExec(datash));
}
