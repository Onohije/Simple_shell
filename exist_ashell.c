#include "ashell.h"

/**
 * exit_ashell - To exits the shell
 * @datash: data relevant (sta and args)
 * Return: 0 on success.
 */
int exit_ashell(data_shell *datash)
{
	unsigned int usta;
	int isDigit;
	int s_len;
	int big_num;

	if (datash->args[1] != NULL)
	{
		usta = _atoi(datash->args[1]);
		isDigit = isdigit_(datash->args[1]);
		s_len = strlen_(datash->args[1]);
		big_num = usta > (unsigned int)INT_MAX;
		if (!isDigit || s_len > 10 || big_num)
		{
			getError(datash, 2);
			datash->sta = 2;
			return (1);
		}
		datash->sta = (usta % 256);
	}
	return (0);
}
