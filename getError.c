#include "ashell.h"

/**
 * getError - Calls the error according the builtin, syntax or permission
 * @datash: Data structure that contains arguments
 * @e_v: Error value
 * Return: error
 */
int getError(data_shell *datash, int e_v)
{
	char *err;

	switch (e_v)
	{
	case -1:
		err = errorEnv(datash);
		break;
	case 126:
		err = errorPath_126(datash);
		break;
	case 127:
		err = errorNotFound(datash);
		break;
	case 2:
		if (strcmp_("exit", datash->args[0]) == 0)
			err = errorExitShell(datash);
		else if (strcmp_("cd", datash->args[0]) == 0)
			err = errorGetCd(datash);
		break;
	}

	if (err)
	{
		write(STDERR_FILENO, err, strlen_(err));
		free(err);
	}

	datash->sta = e_v;
	return (e_v);
}
