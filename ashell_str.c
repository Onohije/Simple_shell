#include "ashell.h"

/**
 * strcat_ - To concatenate two strings
 * @dest: Char pointer the dest of the copied str
 * @src: Const char pointer the source of str
 * Return: The dest
 */
char *strcat_(char *dest, const char *src)
{
	int n;
	int m;

	for (n = 0; dest[n] != '\0'; n++)
		;

	for (m = 0; src[m] != '\0'; m++)
	{
		dest[n] = src[m];
		n++;
	}

	dest[n] = '\0';
	return (dest);
}
/**
 * *strcpy_ - To copies the str pointed to by src.
 * @dest: Type char pointer the dest of the copied str
 * @src: Type char pointer the source of str
 * Return: The dest.
 */
char *strcpy_(char *dest, char *src)
{

	size_t i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';

	return (dest);
}
/**
 * strcmp_ - Function that compares two strings.
 * @s: Type str compared
 * @ss: Type str compared
 * Return: Always 0.
 */
int strcmp_(char *s, char *ss)
{
	int i;

	for (i = 0; s[i] == ss[i] && s[i]; i++)
		;

	if (s[i] > ss[i])
		return (1);
	if (s[i] < ss[i])
		return (-1);
	return (0);
}
/**
 * strchr_ - To locates a character in a str,
 * @s: str
 * @c: character.
 * Return: Pointer to the first occurrence of the character c.
 */
char *strchr_(char *s, char c)
{
	unsigned int n = 0;

	for (; *(s + n) != '\0'; n++)
		if (*(s + n) == c)
			return (s + n);
	if (*(s + n) == c)
		return (s + n);
	return ('\0');
}
/**
 * strspn_ - To gets the length of a prefix substring.
 * @s: initial segment.
 * @acc: accepted bytes.
 * Return: Number of accepted bytes.
 */
int strspn_(char *s, char *acc)
{
	int n, m, bool;

	for (n = 0; *(s + n) != '\0'; n++)
	{
		bool = 1;
		for (m = 0; *(acc + m) != '\0'; m++)
		{
			if (*(s + n) == *(acc + m))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (n);
}
