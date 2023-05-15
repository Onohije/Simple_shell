#include "ashell.h"

/**
 * change_dir_dot - Changes to the parent directory
 *
 * @datash: data relevant (environ)
 *
 * Return: no return
 */
void change_dir_dot(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *d, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = strdup_(pwd);
	setEnv("OLDPWD", cp_pwd, datash);
	d = datash->args[1];
	if (strcmp_(".", d) == 0)
	{
		setEnv("PWD", cp_pwd, datash);
		free(cp_pwd);
		return;
	}
	if (strcmp_("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	rev_str(cp_strtok_pwd);
	cp_strtok_pwd = strtok_(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = strtok_(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_str(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		setEnv("PWD", cp_strtok_pwd, datash);
	}
	else
	{
		chdir("/");
		setEnv("PWD", "/", datash);
	}
	datash->sta = 0;
	free(cp_pwd);
}

/**
 * change_dir_to - Changes to directory given by the user
 *
 * @datash: Data relevant (directories)
 * Return: no return
 */
void change_dir_to(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *d, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	d = datash->args[1];
	if (chdir(d) == -1)
	{
		getError(datash, 2);
		return;
	}

	cp_pwd = strdup_(pwd);
	setEnv("OLDPWD", cp_pwd, datash);

	cp_dir = strdup_(d);
	setEnv("PWD", cp_dir, datash);

	free(cp_pwd);
	free(cp_dir);

	datash->sta = 0;

	chdir(d);
}

/**
 * change_dir_previous - Changes to the previous dir
 *
 * @datash: Data relevant (environ)
 * Return: no return
 */
void change_dir_previous(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = strdup_(pwd);

	p_oldpwd = _getenv("OLDPWD", datash->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = strdup_(p_oldpwd);

	setEnv("OLDPWD", cp_pwd, datash);

	if (chdir(cp_oldpwd) == -1)
		setEnv("PWD", cp_pwd, datash);
	else
		setEnv("PWD", cp_oldpwd, datash);

	p_pwd = _getenv("PWD", datash->_environ);

	write(STDOUT_FILENO, p_pwd, strlen_(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	datash->sta = 0;

	chdir(p_pwd);
}

/**
 * change_dir_to_home - Changes to home dir
 *
 * @datash: Data relevant (environ)
 * Return: no return
 */
void change_dir_to_home(data_shell *datash)
{
	char *p_pwd, *hom;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = strdup_(pwd);

	hom = _getenv("HOME", datash->_environ);

	if (hom == NULL)
	{
		setEnv("OLDPWD", p_pwd, datash);
		free(p_pwd);
		return;
	}

	if (chdir(hom) == -1)
	{
		getError(datash, 2);
		free(p_pwd);
		return;
	}

	setEnv("OLDPWD", p_pwd, datash);
	setEnv("PWD", hom, datash);
	free(p_pwd);
	datash->sta = 0;
}
