#include "ashell.h"

/**
 * swapChar - To swap | and & for non-printed chars
 *
 * @input: Input str
 * @bool: Type of swap
 * Return: Swapped string.
 */
char *swapChar(char *input, int bool)
{
	int n;

	if (bool == 0)
	{
		for (n = 0; input[n]; n++)
		{
			if (input[n] == '|')
			{
				if (input[n + 1] != '|')
					input[n] = 16;
				else
					n++;
			}

			if (input[n] == '&')
			{
				if (input[n + 1] != '&')
					input[n] = 12;
				else
					n++;
			}
		}
	}
	else
	{
		for (n = 0; input[n]; n++)
		{
			input[n] = (input[n] == 16 ? '|' : input[n]);
			input[n] = (input[n] == 12 ? '&' : input[n]);
		}
	}
	return (input);
}

/**
 * addNodes - Adds separators and command lines in the lists
 *
 * @hd_s: Head of separator list
 * @hd_l: Head of command lines list
 * @input: Input string
 * Return: no return value
 */
void addNodes(store_sep **hd_s, store_line **hd_l, char *input)
{
	int n;
	char *ln;

	input = swapChar(input, 0);

	for (n = 0; input[n]; n++)
	{
		if (input[n] == ';')
			addSepNodeEnd(hd_s, input[n]);

		if (input[n] == '|' || input[n] == '&')
		{
			addSepNodeEnd(hd_s, input[n]);
			n++;
		}
	}

	ln = strtok_(input, ";|&");
	do {
		ln = swapChar(ln, 1);
		addLineNodeEnd(hd_l, ln);
		ln = strtok_(NULL, ";|&");
	} while (ln != NULL);

}

/**
 * goNext - Go to the next command line stored
 *
 * @lt_s: Separator list
 * @lt_l: Command line list
 * @datash: data structure
 * Return: no return value.
 */
void goNext(store_sep **lt_s, store_line **lt_l, data_shell *datash)
{
	int lp_sep;
	store_sep *ls_s;
	store_line *ls_l;

	lp_sep = 1;
	ls_s = *lt_s;
	ls_l = *lt_l;

	while (ls_s != NULL && lp_sep)
	{
		if (datash->sta == 0)
		{
			if (ls_s->sep == '&' || ls_s->sep == ';')
				lp_sep = 0;
			if (ls_s->sep == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->sep == '|' || ls_s->sep == ';')
				lp_sep = 0;
			if (ls_s->sep == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !lp_sep)
			ls_s = ls_s->next;
	}

	*lt_s = ls_s;
	*lt_l = ls_l;
}

/**
 * splitCommands - To splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @datash: Data structure
 * @input: Input string
 * Return: 0 to exit and 1 to continue
 */
int splitCommands(data_shell *datash, char *input)
{

	store_sep *hd_s, *lt_s;
	store_line *hd_l, *lt_l;
	int lp;

	hd_s = NULL;
	hd_l = NULL;

	addNodes(&hd_s, &hd_l, input);

	lt_s = hd_s;
	lt_l = hd_l;

	while (lt_l != NULL)
	{
		datash->inpt = lt_l->line;
		datash->args = splitLine(datash->inpt);
		lp = execLine(datash);
		free(datash->args);

		if (lp == 0)
			break;

		goNext(&lt_s, &lt_l, datash);

		if (lt_l != NULL)
			lt_l = lt_l->next;
	}

	freeSepList(&hd_s);
	freeLineList(&hd_l);

	if (lp == 0)
		return (0);
	return (1);
}

/**
 * splitLine - To tokenizes the input string
 *
 * @input: Input str.
 * Return: String splitted.
 */
char **splitLine(char *input)
{
	size_t bs;
	size_t n;
	char **toks;
	char *tok;

	bs = TOK_BUFSIZE;
	toks = malloc(sizeof(char *) * (bs));
	if (toks == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	tok = strtok_(input, TOK_DELIM);
	toks[0] = tok;

	for (n = 1; tok != NULL; n++)
	{
		if (n == bs)
		{
			bs += TOK_BUFSIZE;
			toks = _reallocdp(toks, n, sizeof(char *) * bs);
			if (toks == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		tok = strtok_(NULL, TOK_DELIM);
		toks[n] = tok;
	}

	return (toks);
}
