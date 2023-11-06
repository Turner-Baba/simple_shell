#include "header.h"
/**
 * display_enviros - a function that outputs env variables
 * @tam: a pointer to datashell
 * Return: (0) on success
 */
int display_enviros(datashell *tam)
{
	int a, b;

	for (a = 0; tam->envarias[a]; a++)
	{
		for (b = 0; tam->envarias[a][b]; b++)
			;
		write(STDOUT_FILENO, tam->envarias[a], b);
		write(STDOUT_FILENO, "\n", 1);
	}

	tam->position = 0;
	return (0);
}

/**
 * getenV_ - a function that gets the env variable
 * @id: identity of the env variable
 * @envarias: a pointer to env variables
 * Return: the val of env variable
 */
char *getenV_(const char *id, char **envarias)
{
	int a, estatus = 0;
	char *envptr;

	envptr = NULL;

	for (a = 0; envarias[a]; a++)
	{
		estatus = envarias_comp(envarias[a], id);
		if (estatus)
		{
			envptr = envarias[a];
			break;
		}
	}

	return (envptr + estatus);
}

/**
 * set_enV_ - a function that sets env variables
 * @id: identity of env variable
 * @sig: the value to be assigned to the env varibale
 * @tam: a pointer to the structure
 */
void set_enV_(char *id, char *sig, datashell *tam)
{
	int a;
	char *envcp, *newenv;

	for (a = 0; tam->envarias[a]; a++)
	{
		envcp = dup_string(tam->envarias[a]);
		newenv = tok_string(envcp, "=");

		if (cmp_string(newenv, id) == 0)
		{
			free(tam->envarias[a]);
			tam->envarias[a] = dup_env_stat(newenv, sig);
			free(envcp);
			return;
		}

		free(envcp);
	}

	tam->envarias = _re_alloc_ptr(tam->envarias, a, sizeof(char *) * (a + 2));
	tam->envarias[a] = dup_env_stat(id, sig);
	tam->envarias[a + 1] = NULL;
}

/**
 * unsets_Env - a function that unsets an environment var
 * @tam: a pointer to data structure
 * Return: (0) on code success
 */
int unsets_Env(datashell *tam)
{
	char **reenv;
	char *envcp, *newenv;
	int a, b, c;

	if (tam->arg_tok[1] == NULL)
	{
		find_err(tam, -1);
		return (1);
	}

	c = -1;
	for (a = 0; tam->envarias[a]; a++)
	{
		envcp = dup_string(tam->envarias[a]);
		newenv = tok_string(envcp, "=");
		if (cmp_string(newenv, tam->arg_tok[1]) == 0)
		{
			c = a;
		}
		free(envcp);
	}
	if (c == -1)
	{
		find_err(tam, -1);
		return (1);
	}
	reenv = malloc(sizeof(char *) * (a));
	for (a = b = 0; tam->envarias[a]; a++)
	{
		if (a != c)
		{
			reenv[b] = tam->envarias[a];
			b++;
		}
	}
	reenv[b] = NULL;
	free(tam->envarias[c]);
	free(tam->envarias);
	tam->envarias = reenv;
	return (0);
}
