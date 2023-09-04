#include "ashell.h"

/**
 * c_dir - To checks ":" if is in the current directory.
 * @path: Type char pointer char.
 * @n: Type int pointer of index.
 * Return: 1 if the path is searchable in the cd and 0 otherwise.
 */
int c_dir(char *path, int *n)
{
	if (path[*n] == ':')
		return (1);

	while (path[*n] != ':' && path[*n])
	{
		*n += 1;
	}

	if (path[*n])
		*n += 1;

	return (0);
}

/**
 * is_which - Locates a command
 *
 * @cmd: Command name.
 * @_environ: Environment variable.
 * Return: location of the command.
 */
char *is_which(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *d;
	int l_dir, l_cmd, n;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		ptr_path = strdup_(path);
		l_cmd = strlen_(cmd);
		token_path = strtok_(ptr_path, ":");
		n = 0;
		while (token_path != NULL)
		{
			if (c_dir(path, &n))
				if (stat(cmd, &st) == 0)
					return (cmd);
			l_dir = strlen_(token_path);
			d = malloc(l_dir + l_cmd + 2);
			strcpy_(d, token_path);
			strcat_(d, "/");
			strcat_(d, cmd);
			strcat_(d, "\0");
			if (stat(d, &st) == 0)
			{
				free(ptr_path);
				return (d);
			}
			free(d);
			token_path = strtok_(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * executable_ - To determine if it is an executable
 *
 * @datash: Data structure
 * Return: 0 if it is not an executable and other number if it does
 */
int executable_(data_shell *datash)
{
	struct stat st;
	int n;
	char *input;

	input = datash->args[0];
	for (n = 0; input[n]; n++)
	{
		if (input[n] == '.')
		{
			if (input[n + 1] == '.')
				return (0);
			if (input[n + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[n] == '/' && n != 0)
		{
			if (input[n + 1] == '.')
				continue;
			n++;
			break;
		}
		else
			break;
	}
	if (n == 0)
		return (0);

	if (stat(input + n, &st) == 0)
	{
		return (n);
	}
	getError(datash, 127);
	return (-1);
}

/**
 * checkErrorCmd - To verify if user has permissions to access
 *
 * @dir: Destination directory
 * @datash: Data structure
 * Return: 1 if there is an error and 0 if not
 */
int checkErrorCmd(char *dir, data_shell *datash)
{
	if (dir == NULL)
	{
		getError(datash, 127);
		return (1);
	}

	if (strcmp_(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			getError(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			getError(datash, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * commandExec - To executes command lines
 *
 * @datash: Data relevant (args and input)
 * Return: 1 on success.
 */
int commandExec(data_shell *datash)
{
	pid_t pd;
	pid_t ppd;
	int st;
	int ex;
	char *d;
	(void) ppd;

	ex = executable_(datash);
	if (ex == -1)
		return (1);
	if (ex == 0)
	{
		d = is_which(datash->args[0], datash->_environ);
		if (checkErrorCmd(d, datash) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (ex == 0)
			d = is_which(datash->args[0], datash->_environ);
		else
			d = datash->args[0];
		execve(d + ex, datash->args, datash->_environ);
	}
	else if (pd < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do {
			ppd = waitpid(pd, &st, WUNTRACED);
		} while (!WIFEXITED(st) && !WIFSIGNALED(st));
	}

	datash->sta = st / 256;
	return (1);
}
