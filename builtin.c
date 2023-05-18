#include "ashell.h"

/**
 * getBuiltin - The builtin that pais the command in the arg
 * @cmd: The command for which to retrieve the built-in function pointer.
 * Return: The function pointer of the built-in command.
 */
int (*getBuiltin(char *cmd))(data_shell *)
{
	bull_com builtin[] = {
		{ "env", _env },
		{ "exit", exit_ashell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", change_dir_shell },
		{ "help", getHelp },
		{ NULL, NULL }
	};
	int n;

	for (n = 0; builtin[n].nam; n++)
	{
		if (strcmp_(builtin[n].nam, cmd) == 0)
			break;
	}

	return (builtin[n].fun);
}
