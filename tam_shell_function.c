#include "header.h"
/**
 * find_signal - a function that handles signal
 * @signal: the signal
 * Return: void
 */
void find_signal(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n:> ", 4);
}

/**
 * find_err - a function that handles error message
 * @tam: a pointer to datashell structure
 * @errval: value of error
 * Return: the error on code
 */
int find_err(datashell *tam, int errval)
{
	char *emsg = NULL;

	switch (errval)
	{
		case -1:
			emsg = settings_emsg(tam);
			break;
		case 126:
			emsg = path126_emsg(tam);
			break;
		case 127:
			emsg = cmd_invalid(tam);
			break;
		case 2:
			if (cmp_string("exit", tam->arg_tok[0]) == 0)
				emsg = exit_shell_error(tam);
			else if (cmp_string("cd", tam->arg_tok[0]) == 0)
				emsg = path_error(tam);
			break;
	}

	if (emsg)
	{
		write(STDERR_FILENO, emsg, _lenstr(emsg));
		free(emsg);
	}

	tam->position = errval;

	return (errval);
}

/**
 * find_inbuilt - a function that gets a ptr to builtins func
 * @cmnd: string
 * Return: a pointer to the inbuilt func
 */
int (*find_inbuilt(char *cmnd))(datashell *)
{
	inbuilt_t inbuilt[] = {
		{ "env", display_enviros },
		{ "exit", closeshell },
		{ "setenv", _setenV_ },
		{ "unsetenv", unsets_Env },
		{ "cd", goto_shell },
		{ "help", handles_help },
		{ NULL, NULL }
	};

	int a;

	for (a = 0; inbuilt[a].id; a++)
	{
		if (cmp_string(inbuilt[a].id, cmnd) == 0)
			break;
	}

	return (inbuilt[a].f);
}

/**
 * handles_help - a function that handles help msg for commands
 * @tam: a pointer to datashell structure
 * Return: (0) on success
 */
int handles_help(datashell *tam)
{
	if (tam->arg_tok[1] == 0)
		general_help_data();
	else if (cmp_string(tam->arg_tok[1], "setenv") == 0)
		setEnv_support_data();
	else if (cmp_string(tam->arg_tok[1], "env") == 0)
		enVsupport_data();
	else if (cmp_string(tam->arg_tok[1], "unsetenv") == 0)
		unsetsEnv_support();
	else if (cmp_string(tam->arg_tok[1], "help") == 0)
		support_data();
	else if (cmp_string(tam->arg_tok[1], "exit") == 0)
		close_guide_data();
	else if (cmp_string(tam->arg_tok[1], "cd") == 0)
		chdir_guide_info();
	else if (cmp_string(tam->arg_tok[1], "alias") == 0)
		supportalias_data();
	else
		write(STDERR_FILENO, tam->arg_tok[0],
				_lenstr(tam->arg_tok[0]));
	tam->position = 0;
	return (1);
}
