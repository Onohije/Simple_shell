#include "ashell.h"

/**
 * errorEnv - Generates an error message for the "env" command in the getEnv function.
 * @datash: Data relevant
 * Return: Error msg.
 */
char *errorEnv(data_shell *datash)
{
	int l;
	char *err;
	char *v_str;
	char *ms;

	v_str = auxItoa(datash->contn);
	ms = ": Unable to add/remove from environment\n";
	l = strlen_(datash->av[0]) + strlen_(v_str);
	l += strlen_(datash->args[0]) + strlen_(ms) + 4;
	err = malloc(sizeof(char) * (l + 1));
	if (err == 0)
	{
		free(err);
		free(v_str);
		return (NULL);
	}

	strcpy_(err, datash->av[0]);
	strcat_(err, ": ");
	strcat_(err, v_str);
	strcat_(err, ": ");
	strcat_(err, datash->args[0]);
	strcat_(err, ms);
	strcat_(err, "\0");
	free(v_str);

	return (err);
}
/**
 * errorPath_126 - Error msg for path and failure denied permission.
 * @datash: Data relevant.
 *
 * Return: The error string.
 */
char *errorPath_126(data_shell *datash)
{
	int l;
	char *v_str;
	char *err;

	v_str = auxItoa(datash->contn);
	l = strlen_(datash->av[0]) + strlen_(v_str);
	l += strlen_(datash->args[0]) + 24;
	err = malloc(sizeof(char) * (l + 1));
	if (err == 0)
	{
		free(err);
		free(v_str);
		return (NULL);
	}
	strcpy_(err, datash->av[0]);
	strcat_(err, ": ");
	strcat_(err, v_str);
	strcat_(err, ": ");
	strcat_(err, datash->args[0]);
	strcat_(err, ": Permission denied\n");
	strcat_(err, "\0");
	free(v_str);
	return (err);
}
