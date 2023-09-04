#include "ashell.h"

/**
 * strcatCd - The function that concatenates the message for cd error.
 *
 * @datash: data relevant to the error.
 * @ms: Message to print.
 * @err: Output message.
 * @v_str: Counter lines.
 * Return: Error message.
 */
char *strcatCd(data_shell *datash, char *ms, char *err, char *v_str)
{
	char *ill_flag;

	strcpy_(err, datash->av[0]);
	strcat_(err, ": ");
	strcat_(err, v_str);
	strcat_(err, ": ");
	strcat_(err, datash->args[0]);
	strcat_(err, ms);
	if (datash->args[1][0] == '-')
	{
		ill_flag = malloc(3);
		ill_flag[0] = '-';
		ill_flag[1] = datash->args[1][1];
		ill_flag[2] = '\0';
		strcat_(err, ill_flag);
		free(ill_flag);
	}
	else
	{
		strcat_(err, datash->args[1]);
	}

	strcat_(err, "\n");
	strcat_(err, "\0");
	return (err);
}

/**
 * errorGetCd - The  error msg for cd cmd in getCd
 * @datash: The data relevant (directory)
 * Return: Error msg
 */
char *errorGetCd(data_shell *datash)
{
	int l, lenId;
	char *err, *v_str, *ms;

	v_str = auxItoa(datash->contn);
	if (datash->args[1][0] == '-')
	{
		ms = ": Illegal option ";
		lenId = 2;
	}
	else
	{
		ms = ": can not cd to ";
		lenId = strlen_(datash->args[1]);
	}

	l = strlen_(datash->av[0]) + strlen_(datash->args[0]);
	l += strlen_(v_str) + strlen_(ms) + lenId + 5;
	err = malloc(sizeof(char) * (l + 1));

	if (err == 0)
	{
		free(v_str);
		return (NULL);
	}

	err = strcatCd(datash, ms, err, v_str);

	free(v_str);

	return (err);
}

/**
 * errorNotFound - The generic error msg for cmd not found
 * @datash: data relevant
 * Return: Error msg
 */
char *errorNotFound(data_shell *datash)
{
	int l;
	char *err;
	char *v_str;

	v_str = auxItoa(datash->contn);
	l = strlen_(datash->av[0]) + strlen_(v_str);
	l += strlen_(datash->args[0]) + 16;
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
	strcat_(err, ": not found\n");
	strcat_(err, "\0");
	free(v_str);
	return (err);
}

/**
 * errorExitShell - To generic error msg for exit in getExit
 * @datash: data relevant (counter, arguments).
 *
 * Return: Error msg.
 */
char *errorExitShell(data_shell *datash)
{
	int l;
	char *err;
	char *v_str;

	v_str = auxItoa(datash->contn);
	l = strlen_(datash->av[0]) + strlen_(v_str);
	l += strlen_(datash->args[0]) + strlen_(datash->args[1]) + 23;
	err = malloc(sizeof(char) * (l + 1));
	if (err == 0)
	{
		free(v_str);
		return (NULL);
	}
	strcpy_(err, datash->av[0]);
	strcat_(err, ": ");
	strcat_(err, v_str);
	strcat_(err, ": ");
	strcat_(err, datash->args[0]);
	strcat_(err, ": Illegal number: ");
	strcat_(err, datash->args[1]);
	strcat_(err, "\n\0");
	free(v_str);

	return (err);
}
