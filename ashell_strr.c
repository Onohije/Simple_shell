#include "ashell.h"

/**
 * strdup_ -  Duplicates a string in heap memory.
 * @s: Type char pointer str
 * Return: Duplicated str
 */
char *strdup_(const char *s)
{
	char *nw;
	size_t l;

	l = strlen_(s);
	nw = malloc(sizeof(char) * (l + 1));
	if (nw == NULL)
		return (NULL);
	_memcpy(nw, s, l + 1);
	return (nw);
}

/**
 * strlen_ - The lenght of a string.
 * @s: Type char pointer
 * Return: Always 0.
 */
int strlen_(const char *s)
{
	int l;

	for (l = 0; s[l] != 0; l++)
	{
	}
	return (l);
}

/**
 * cmpChars - To compare chars of strings
 * @str: input string.
 * @dim: delimiter.
 *
 * Return: 1 if are equals and 0 if not.
 */
int cmpChars(char str[], const char *dim)
{
	unsigned int n, m, i;

	for (n = 0, i = 0; str[n]; n++)
	{
		for (m = 0; dim[m]; m++)
		{
			if (str[n] == dim[m])
			{
				i++;
				break;
			}
		}
	}
	if (n == i)
		return (1);
	return (0);
}

/**
 * strtok_ - To splits a string by some delimiter.
 * @str: input string.
 * @dim: delimiter.
 *
 * Return: string splited.
 */
char *strtok_(char str[], const char *dim)
{
	static char *sptt, *strEnd;
	char *strStart;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (cmpChars(str, dim))
			return (NULL);
		sptt = str; /*Store first address*/
		i = strlen_(str);
		strEnd = &str[i]; /*Store last address*/
	}
	strStart = sptt;
	if (strStart == strEnd) /*Reaching the end*/
		return (NULL);

	for (bool = 0; *sptt; sptt++)
	{
		/*Breaking loop finding the next token*/
		if (sptt != strStart)
			if (*sptt && *(sptt - 1) == '\0')
				break;
		/*Replacing delimiter for null char*/
		for (i = 0; dim[i]; i++)
		{
			if (*sptt == dim[i])
			{
				*sptt = '\0';
				if (sptt == strStart)
					strStart++;
				break;
			}
		}
		if (bool == 0 && *sptt) /*Str != Delim*/
			bool = 1;
	}
	if (bool == 0) /*Str == Delim*/
		return (NULL);
	return (strStart);
}

/**
 * isdigit_ - defines if str passed is a num
 *
 * @s: input str
 * Return: 1 if str is a num and 0 in other case.
 */
int isdigit_(const char *s)
{
	unsigned int n;

	for (n = 0; s[n]; n++)
	{
		if (s[n] < 48 || s[n] > 57)
			return (0);
	}
	return (1);
}
