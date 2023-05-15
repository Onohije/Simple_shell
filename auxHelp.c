#include "ashell.h"

/**
 * auxHelpEnv - To help information for the builtin env
 * Return: no return
 */
void auxHelpEnv(void)
{
	char *h = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, h, strlen_(h));
	h = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, h, strlen_(h));

}
/**
 * auxHelpSetenv -To help information for the builtin setenv
 * Return: no return
 */
void auxHelpSetenv(void)
{

	char *h = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, h, strlen_(h));
	h = "int replace)\n\t";
	write(STDOUT_FILENO, h, strlen_(h));
	h = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, h, strlen_(h));
}
/**
 * auxHelpUnsetenv -  To help information for the builtin unsetenv
 * Return: no return
 */
void auxHelpUnsetenv(void)
{
	char *h = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, h, strlen_(h));
	h = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, h, strlen_(h));
}


/**
 * auxHelpGeneral - Entry point for help information for the help builtin
 * Return: no return
 */
void auxHelpGeneral(void)
{
	char *h = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, h, strlen_(h));
	h = "These cmd are defined internally.Type 'h' to see the list";
	write(STDOUT_FILENO, h, strlen_(h));
	h = "Type 'h nam' to find out more about the function 'nam'.\n\n ";
	write(STDOUT_FILENO, h, strlen_(h));
	h = " alias: alias [nam=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, h, strlen_(h));
	h = "[dir]\nexit: exit [n]\n  env: env [option] [nam=value] [command ";
	write(STDOUT_FILENO, h, strlen_(h));
	h = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, h, strlen_(h));
	h = "unsetenv [variable]\n";
	write(STDOUT_FILENO, h, strlen_(h));
}
/**
 * auxHelpExit - To help information fot the builint exit
 * Return: no return
 */
void auxHelpExit(void)
{
	char *h = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, h, strlen_(h));
	h = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, h, strlen_(h));
	h = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, h, strlen_(h));
}
