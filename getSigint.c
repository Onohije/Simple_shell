#include "ashell.h"

/**
 * getSigint - To handle the crtl + c call in prompt
 * @s: Signal handler
 */
void getSigint(int s)
{
	(void)s;
	write(STDOUT_FILENO, "\n@-@ ", 5);
}
