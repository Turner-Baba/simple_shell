#include "header.h"
/**
 * closeshell - a function that closes the shell
 * @tam: a pointer to datashell structure
 * Return: (0) on code success
 */
int closeshell(datashell *tam)
{
	unsigned int closesh;
	int digits, sh_lent, sum;

	if (tam->arg_tok[1] != NULL)
	{
		closesh = str_atoi(tam->arg_tok[1]);
		digits = _number(tam->arg_tok[1]);
		sh_lent = _lenstr(tam->arg_tok[1]);
		sum = closesh > (unsigned int) INT_MAX;
		if (!digits || sh_lent > 10 || sum)
		{
			find_err(tam, 2);
			tam->position = 2;
			return (1);
		}

		tam->position = (closesh % 256);
	}

	return (0);
}

/**
 * handles_cdline - a function thats handles and executes the commandlines
 * @tam: a pointer to datashell structure
 * Return: (1) on success
 */
int handles_cdline(datashell *tam)
{
	pid_t dp;
	pid_t wdp;
	int ps = 0;
	int handles;
	char *path;
	(void) wdp;

	handles = exm_execc(tam);
	if (handles == -1)
		return (-1);
	if (handles == 0)
	{
		path = execute_path(tam->arg_tok[0], tam->envarias);
		if (exm_perm(path, tam) == 1)
			return (1);
	}

	dp = fork();
	if (dp == 0)
	{
		if (handles == 0)
			path = execute_path(tam->arg_tok[0], tam->envarias);
		else
			path = tam->arg_tok[0];
		execve(path + handles, tam->arg_tok, tam->envarias);
	}
	else if (dp < 0)
	{
		perror(tam->argv[0]);
		return (1);
	}
	else
	{
		do {
			wdp = waitpid(dp, &ps, WUNTRACED);
		} while (!WIFEXITED(ps) && !WIFSIGNALED(ps));
	}
	tam->position = ps / 256;
	return (1);
}

/**
 * handles_cmnd - a function that handles and executes commands
 * @tam: a pointer to datashell structure
 * Return: (0) on success
 */
int handles_cmnd(datashell *tam)
{
	int (*inbuilt)(datashell *tam);

	if (tam->arg_tok[0] == NULL)
		return (0);
	inbuilt = find_inbuilt(tam->arg_tok[0]);
	if (inbuilt != NULL)
		return (inbuilt(tam));

	return (handles_cdline(tam));
}
