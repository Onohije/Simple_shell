#include "ashell.h"

/**
 * auxHelp - To help information for the builtin help.
 * Return: no return
 */
void auxHelp(void)
{
	char *h = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, h, strlen_(h));
	h = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, h, strlen_(h));
	h = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, h, strlen_(h));
}
/**
 * auxHelpAlias - To help information for the builtin alias.
 * Return: no return
 */
void auxHelp_alias(void)
{
	char *h = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, h,  strlen_(h));
	h = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, h, strlen_(h));
}
/**
 * auxHelpCd - To help information for the builtin alias.
 * Return: no return
 */
void auxHelp_cd(void)
{
	char *h = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, h, strlen_(h));
	h = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, h, strlen_(h));
}
