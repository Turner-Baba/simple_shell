#include "header.h"
/**
 * data_initialize - a function that initializes data
 * @tam: a pointer to structure
 * @av: the argument vector
 * Return: void
 */
void data_initialize(datashell *tam, char **av)
{
	unsigned int a;

	tam->argv = av;
	tam->cdline = NULL;
	tam->arg_tok = NULL;
	tam->position = 0;
	tam->ln_index = 1;

	for (a = 0; environ[a]; a++)
		;
	tam->envarias = malloc(sizeof(char *) * (a + 1));

	for (a = 0; environ[a]; a++)
	{
		tam->envarias[a] = dup_string(environ[a]);
	}

	tam->envarias[a] = NULL;
	tam->pid = string_fmt(getpid());
}

/**
 * data_release - a function that releases data
 * @tam: a pointer to a struct
 * Return: void
 */
void data_release(datashell *tam)
{
	unsigned int a;

	for (a = 0; tam->envarias[a]; a++)
	{
		free(tam->envarias[a]);
	}

	free(tam->envarias);
	free(tam->pid);
}

/**
 * main - entry point of my code
 * @ac: the argument count
 * @av: the argument vector
 * Return: (0) on code success
 */
int main(int ac, char **av)
{
	datashell tam;
	(void) ac;

	signal(SIGINT, find_signal);
	data_initialize(&tam, av);
	opens_sh(&tam);
	data_release(&tam);

	if (tam.position < 0)
		return (255);

	return (tam.position);
}
