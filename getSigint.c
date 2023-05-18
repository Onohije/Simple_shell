#include "ashell.h"

/**
 * getSigint - Signal handler for handling the Ctrl + C signal in the prompt
 * @s: Signal handler
 */
void getSigint(int s)
{
	(void)s;
	write(STDOUT_FILENO, "\n@-@ ", 5);
}
