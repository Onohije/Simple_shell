#include "ashell.h"

/**
 * getLen - To get the lenght of an integer num.
 * @n: Type int num.
 * Return: Lenght of the num.
 */
int getLen(int n)
{
	unsigned int l;
	int len = 1;

	if (n < 0)
	{
		len++;
		l = n * -1;
	}
	else
	{
		l = n;
	}
	while (l > 9)
	{
		len++;
		l = l / 10;
	}

	return (len);
}
/**
 * auxItoa - To function converts int to str.
 * @n: Type int num.
 * Return: Str.
 */
char *auxItoa(int n)
{
	unsigned int l;
	int len = getLen(n);
	char *buf;

	buf = malloc(sizeof(char) * (len + 1));
	if (buf == 0)
		return (NULL);

	*(buf + len) = '\0';

	if (n < 0)
	{
		l = n * -1;
		buf[0] = '-';
	}
	else
	{
		l = n;
	}

	len--;
	do {
		*(buf + len) = (l % 10) + '0';
		l = l / 10;
		len--;
	}
	while (l > 0)
		;
	return (buf);
}

/**
 * _atoi - To converts a string to an integer.
 * @s: Input str.
 * Return: integer.
 */
int _atoi(char *s)
{
	unsigned int count = 0, size = 0, u = 0, n = 1, m = 1, i;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;
		if (*(s + count) == '-')
		       n *= -1;

		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		u = u + ((*(s + i) - 48) * m);
		m /= 10;
	}
	return (u * n);
}
