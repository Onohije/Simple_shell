#include "ashell.h"

/**
 * cmpEnvName - To compares env variables names
 * with the name passed.
 * @env_name: Name of the environment variable
 * @n: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int cmpEnvName(const char *env_name, const char *n)
{
	int m;

	for (m = 0; env_name[m] != '='; m++)
	{
		if (env_name[m] != n[m])
		{
			return (0);
		}
	}

	return (m + 1);
}

/**
 * _getenv - To get an environment variable
 * @n: Name of the environment variable
 * @_environ: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *_getenv(const char *n, char **_environ)
{
	char *pt_env;
	int a, m;

	/* Initialize ptr_env value */
	pt_env = NULL;
	m = 0;
	/* Compare all environment variables */
	for (a = 0; _environ[a]; a++)
	{
		/* If name and env are equal */
		m = cmpEnvName(_environ[a], n);
		if (m)
		{
			pt_env = _environ[a];
			break;
		}
	}

	return (pt_env + m);
}

/**
 * _env - prints the evironment variables
 *
 * @datash: data relevant.
 * Return: 1 on success.
 */
int _env(data_shell *datash)
{
	int n, m;

	for (n = 0; datash->_environ[n]; n++)
	{

		for (m = 0; datash->_environ[n][m]; m++)
			;

		write(STDOUT_FILENO, datash->_environ[n], m);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->sta = 0;

	return (1);
}
