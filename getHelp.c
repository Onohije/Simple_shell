#include "ashell.h"

/**
 * getHelp - The function that retrieves help mgs according builtin
 * @datash: Data structure (args and input)
 * Return: Return 0
*/
int getHelp(data_shell *datash)
{

	if (datash->args[1] == 0)
		auxHelpGeneral();
	else if (strcmp_(datash->args[1], "setenv") == 0)
		auxHelpSetenv();
	else if (strcmp_(datash->args[1], "env") == 0)
		auxHelpEnv();
	else if (strcmp_(datash->args[1], "unsetenv") == 0)
		auxHelpUnsetenv();
	else if (strcmp_(datash->args[1], "help") == 0)
		auxHelp();
	else if (strcmp_(datash->args[1], "exit") == 0)
		auxHelpExit();
	else if (strcmp_(datash->args[1], "cd") == 0)
		auxHelp_cd();
	else if (strcmp_(datash->args[1], "alias") == 0)
		auxHelp_alias();
	else
		write(STDERR_FILENO, datash->args[0],
		      strlen_(datash->args[0]));

	datash->sta = 0;
	return (1);
}
