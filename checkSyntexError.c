#include "ashell.h"

/**
 * repeatedChar - Counts the repetitions of a char
 *
 * @input: Input str
 * @c: index
 * Return: repetitions
 */
int repeatedChar(char *input, int c)
{
	if (*(input - 1) == *input)
		return (repeatedChar(input - 1, c + 1));

	return (c);
}

/**
 * errorSepOp - To finds syntax errors
 *
 * @input: input str
 * @c: index
 * @ls: The last char read
 * Return: index of error ans  0 when there are no errors
 */
int errorSepOp(char *input, int c, char ls)
{
	int con;

	con = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (errorSepOp(input + 1, c + 1, ls));

	if (*input == ';')
		if (ls == '|' || ls == '&' || ls == ';')
			return (c);

	if (*input == '|')
	{
		if (ls == ';' || ls == '&')
			return (c);

		if (ls == '|')
		{
			con = repeatedChar(input, 0);
			if (con == 0 || con > 1)
				return (c);
		}
	}

	if (*input == '&')
	{
		if (ls == ';' || ls == '|')
			return (c);

		if (ls == '&')
		{
			con = repeatedChar(input, 0);
			if (con == 0 || con > 1)
				return (c);
		}
	}

	return (errorSepOp(input + 1, c + 1, *input));
}

/**
 * firstChar - To finds index of the first char
 *
 * @input: Input str
 * @c: Index
 * Return: 1 if there is an error and 0 in other case.
 */
int firstChar(char *input, int *c)
{

	for (*c = 0; input[*c]; *c += 1)
	{
		if (input[*c] == ' ' || input[*c] == '\t')
			continue;

		if (input[*c] == ';' || input[*c] == '|' || input[*c] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_error - To prints when a syntax error is found
 *
 * @datash: Data structure
 * @input: Input str
 * @c: Index of the error
 * @bool: To control msg error
 * Return: No return
 */
void printSyntaxError(data_shell *datash, char *input, int c, int bool)
{
	char *ms, *mss, *msss, *err, *counter;
	int len;

	if (input[c] == ';')
	{
		if (bool == 0)
			ms = (input[c + 1] == ';' ? ";;" : ";");
		else
			ms = (input[c - 1] == ';' ? ";;" : ";");
	}

	if (input[c] == '|')
		ms = (input[c + 1] == '|' ? "||" : "|");

	if (input[c] == '&')
		ms = (input[c + 1] == '&' ? "&&" : "&");

	mss = ": Syntax error: \"";
	msss = "\" unexpected\n";
	counter = auxItoa(datash->contn);
	len = strlen_(datash->av[0]) + strlen_(counter);
	len += strlen_(ms) + strlen_(mss) + strlen_(msss) + 2;

	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(counter);
		return;
	}
	strcpy_(err, datash->av[0]);
	strcat_(err, ": ");
	strcat_(err, counter);
	strcat_(err, mss);
	strcat_(err, ms);
	strcat_(err, msss);
	strcat_(err, "\0");

	write(STDERR_FILENO, err, len);
	free(err);
	free(counter);
}

/**
 * checkSyntaxError - To intermediate function to
 * find and print a syntax error
 *
 * @datash: Data structure
 * @input: Input string
 * Return: 1 if there is an error and 0 in other case
 */
int checkSyntaxError(data_shell *datash, char *input)
{
	int b = 0;
	int fchar = 0;
	int c = 0;

	fchar = firstChar(input, &b);
	if (fchar == -1)
	{
		printSyntaxError(datash, input, b, 0);
		return (1);
	}

	c = errorSepOp(input + b, 0, *(input + b));
	if (c != 0)
	{
		printSyntaxError(datash, input, b + c, 1);
		return (1);
	}

	return (0);
}
