#include "ashell.h"

/**
 * del_comment - Deletes comments from the input
 *
 * @in: Input str
 * Return: Input without comments.
 */
char *del_comment(char *in)
{
	int n, pt;

	pt = 0;
	for (n = 0; in[n]; n++)
	{
		if (in[n] == '#')
		{
			if (n == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[n - 1] == ' ' || in[n - 1] == '\t' || in[n - 1] == ';')
				pt = n;
		}
	}

	if (pt != 0)
	{
		in = _realloc(in, n, pt + 1);
		in[pt] = '\0';
	}

	return (in);
}

/**
 * shellLoop - Loop of shell
 * @datash: Data relevant (av, input, args).
 *
 * Return: no return value.
 */
void shellLoop(data_shell *datash)
{
	int lp, i;
	char *input;

	lp = 1;
	while (lp == 1)
	{
		write(STDIN_FILENO, "@-@ ", 4);
		input = readLine(&i);
		if (i != -1)
		{
			input = del_comment(input);
			if (input == NULL)
				continue;

			if (checkSyntaxError(datash, input) == 1)
			{
				datash->sta = 2;
				free(input);
				continue;
			}
			input = repVar(input, datash);
			lp = splitCommands(datash, input);
			datash->contn += 1;
			free(input);
		}
		else
		{
			lp = 0;
			free(input);
		}
	}
}
