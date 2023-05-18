#include "ashell.h"

/**
 * line - Assigns the line var for getLine
 * @lineptr: Buffer that store the input str
 * @buf: str that is been called to line
 * @i: size of line
 * @j: size of buffer
 */
void line(char **lineptr, size_t *i, char *buf, size_t j)
{

	if (*lineptr == NULL)
	{
		if  (j > BUFSIZE)
			*i = j;

		else
			*i = BUFSIZE;
		*lineptr = buf;
	}
	else if (*i < j)
	{
		if (j > BUFSIZE)
			*i = j;
		else
			*i = BUFSIZE;
		*lineptr = buf;
	}
	else
	{
		strcpy_(*lineptr, buf);
		free(buf);
	}
}
/**
 * getLine - To  Read inpt from stream
 * @lineptr: Buffer that stores the input
 * @i: Size of lineptr
 * @stream: stream to read from
 * Return: The number of bytes
 */
ssize_t getLine(char **lineptr, size_t *i, FILE *stream)
{
	int j;
	static ssize_t input;
	ssize_t ret_val;
	char *buf;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buf = malloc(sizeof(char) * BUFSIZE);
	if (buf == 0)
		return (-1);
	while (t != '\n')
	{
		j = read(STDIN_FILENO, &t, 1);
		if (j == -1 || (j == 0 && input == 0))
		{
			free(buf);
			return (-1);
		}
		if (j == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buf = _realloc(buf, input, input + 1);
		buf[input] = t;
		input++;
	}
	buf[input] = '\0';
	line(lineptr, i, buf, input);
	ret_val = input;
	if (j != 0)
		input = 0;
	return (ret_val);
}
