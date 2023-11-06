#include "header.h"
/**
 * goto_parent_dir - a function that changes to parent dir
 * @tam: a pointer to datashell structure
 * Return: void
 */
void goto_parent_dir(datashell *tam)
{
	char cwd[PATH_MAX];
	char *folder, *cwdc, *divcwd;

	getcwd(cwd, sizeof(cwd));
	cwdc = dup_string(cwd);
	set_enV_("OLDPWD", cwdc, tam);
	folder = tam->arg_tok[1];
	if (cmp_string(".", folder) == 0)
	{
		set_enV_("PWD", cwd, tam);
		free(cwdc);
		return;
	}

	if (cmp_string("/", cwdc) == 0)
	{
		free(cwdc);
		return;
	}
	divcwd = cwdc;
	rev_string(divcwd);
	divcwd = tok_string(divcwd, "/");
	if (divcwd != NULL)
	{
		divcwd = tok_string(NULL, "\0");
		if (divcwd != NULL)
			rev_string(divcwd);
	}
	if (divcwd != NULL)
	{
		chdir(divcwd);
		set_enV_("PWD", divcwd, tam);
	}
	else
	{
		chdir("/");
		set_enV_("PWD", "/", tam);
	}
	tam->position = 0;
	free(cwdc);
}

/**
 * goto_path - a function that goes to a specified dir
 * @tam: a pointer to datashell structure
 * Return: void
 */
void goto_path(datashell *tam)
{
	char cwd[PATH_MAX];
	char *folder, *cwdc, *cfld;

	getcwd(cwd, sizeof(cwd));
	folder = tam->arg_tok[1];
	if (chdir(folder) == -1)
	{
		find_err(tam, 2);
		return;
	}

	cwdc = dup_string(cwd);
	set_enV_("OLDPWD", cwdc, tam);
	cfld = dup_string(folder);
	set_enV_("PWD", cfld, tam);
	free(cwdc);
	free(cfld);
	tam->position = 0;
	chdir(folder);
}

/**
 * goto_prev - a function that changes to prev dir
 * @tam: a pointer to structure
 * Return: void
 */
void goto_prev(datashell *tam)
{
	char cwd[PATH_MAX];
	char *cwdp, *ocwdd, *cwdc, *cwdcpy;

	getcwd(cwd, sizeof(cwd));
	cwdc = dup_string(cwd);
	ocwdd = getenV_("OLDPWD", tam->envarias);
	if (ocwdd == NULL)
		cwdcpy = cwdc;
	else
		cwdcpy = dup_string(ocwdd);
	set_enV_("OLDPWD", cwdc, tam);
	if (chdir(cwdcpy) == -1)
		set_enV_("PWD", cwdc, tam);
	else
		set_enV_("PWD", cwdcpy, tam);
	cwdp = getenV_("PWD", tam->envarias);
	write(STDOUT_FILENO, cwdp, _lenstr(cwdp));
	write(STDOUT_FILENO, "\n", 1);
	free(cwdc);
	if (ocwdd)
		free(cwdcpy);
	tam->position = 0;
	chdir(cwdp);
}

/**
 * goto_home - a function that goes to home dir
 * @tam: a pointer
 * Return: void
 */
void goto_home(datashell *tam)
{
	char cwd[PATH_MAX];
	char *cwdp, *user;

	getcwd(cwd, sizeof(cwd));
	cwdp = dup_string(cwd);
	user = getenV_("HOME", tam->envarias);
	if (user == NULL)
	{
		set_enV_("OLDPWD", cwdp, tam);
		free(cwdp);
		return;
	}

	if (chdir(user) == -1)
	{
		find_err(tam, 2);
		free(cwdp);
		return;
	}

	set_enV_("OLDPWD", cwdp, tam);
	set_enV_("PWD", user, tam);
	free(cwdp);
	tam->position = 0;
}

/**
 * goto_shell - a funtion goes to shell
 * @tam: a pointer
 * Return: (1) on code success
 */
int goto_shell(datashell *tam)
{
	char *folder;
	int path, home, prev;

	folder = tam->arg_tok[1];
	if (folder != NULL)
	{
		path = cmp_string("$HOME", folder);
		home = cmp_string("~", folder);
		prev = cmp_string("--", folder);
	}

	if (folder == NULL || path || home || prev)
	{
		goto_home(tam);
		return (1);
	}

	if (cmp_string("-", folder) == 0)
	{
		goto_prev(tam);
		return (1);
	}

	if (cmp_string(".", folder) == 0 || cmp_string("..", folder) == 0)
	{
		goto_parent_dir(tam);
		return (1);
	}

	goto_path(tam);
	return (1);
}
