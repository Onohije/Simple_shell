#include "ashell.h"

/**
 * copyInfo - To copies info
 * @n: Name of the environment variable or alias
 * @v: Value of the environment variable or alias.
 *
 * Return: New env or alias.
 */
char *copyInfo(char *n, char *v)
{
	char *nw;
	int ln, lv, l;

	ln = strlen_(n);
	lv = strlen_(v);
	l = ln + lv + 2;
	nw = malloc(sizeof(char) * (l));
	strcpy_(nw, n);
	strcat_(nw, "=");
	strcat_(nw, v);
	strcat_(nw, "\0");

	return (nw);
}

/**
 * setEnv - To sets an environment variable
 *
 * @n: Name of the environment variable
 * @v: Value of the environment variable
 * @datash: Data structure (environ)
 * Return: No return
 */
void setEnv(char *n, char *v, data_shell *datash)
{
	int m;
	char *v_env, *n_env;

	for (m = 0; datash->_environ[m]; m++)
	{
		v_env = strdup_(datash->_environ[m]);
		n_env = strtok_(v_env, "=");
		if (strcmp_(n_env, n) == 0)
		{
			free(datash->_environ[m]);
			datash->_environ[m] = copyInfo(n_env, v);
			free(v_env);
			return;
		}
		free(v_env);
	}

	datash->_environ = _reallocdp(datash->_environ, m, sizeof(char *) * (m + 2));
	datash->_environ[m] = copyInfo(n, v);
	datash->_environ[m + 1] = NULL;
}

/**
 * _setenv - Compares env variables names
 * with the name passed.
 * @datash: Data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _setenv(data_shell *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		getError(datash, -1);
		return (1);
	}

	setEnv(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * _unsetenv - Deletes a environment variable
 *
 * @datash: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv(data_shell *datash)
{
	char **realloc_environ;
	char *v_env, *n_env;
	int a, b, c;

	if (datash->args[1] == NULL)
	{
		getError(datash, -1);
		return (1);
	}
	c = -1;
	for (a = 0; datash->_environ[a]; a++)
	{
		v_env = strdup_(datash->_environ[a]);
		n_env = strtok_(v_env, "=");
		if (strcmp_(n_env, datash->args[1]) == 0)
		{
			c = a;
		}
		free(v_env);
	}
	if (c == -1)
	{
		getError(datash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (a));
	for (a = b = 0; datash->_environ[a]; a++)
	{
		if (a != c)
		{
			realloc_environ[b] = datash->_environ[a];
			b++;
		}
	}
	realloc_environ[b] = NULL;
	free(datash->_environ[c]);
	free(datash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}
