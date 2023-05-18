#include "ashell.h"

/**
 * rev_str - Reverses a string.
 * @s: input str.
 * Return: no return value.
 */
void rev_str(char *s)
{
	int count = 0, n, m;
	char *str, temp;

	while (count >= 0)
	{
		if (s[count] == '\0')
			break;
		count++;
	}
	str = s;

	for (n = 0; n < (count - 1); n++)
	{
		for (m = n + 1; m > 0; m--)
		{
			temp = *(str + m);
			*(str + m) = *(str + (m - 1));
			*(str + (m - 1)) = temp;
		}
	}
}
