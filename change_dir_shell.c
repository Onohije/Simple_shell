#include "ashell.h"

/**
 * change_dir_shell - Changes current dir
 *
 * @datash: Data relevant
 * Return: 1 on success
 */
int change_dir_shell(data_shell *datash)
{
	char *d;
	int ih, ihh, idd;

	d = datash->args[1];

	if (d != NULL)
	{
		ih = strcmp_("$HOME", d);
		ihh = strcmp_("~", d);
		idd = strcmp_("--", d);
	}

	if (d == NULL || !ih || !ihh || !idd)
	{
		change_dir_to_home(datash);
		return (1);
	}

	if (strcmp_("-", d) == 0)
	{
		change_dir_previous(datash);
		return (1);
	}

	if (strcmp_(".", d) == 0 || strcmp_("..", d) == 0)
	{
		change_dir_dot(datash);
		return (1);
	}

	change_dir_to(datash);

	return (1);
}
