#include "header.h"

/**
 * enVsupport_data - gives the info for the 'env' command
 * Return: void
 */

void enVsupport_data(void)
{
	char *support = "env: env [option] [name=value] [command] [args]\n\t";

	write(STDOUT_FILENO, support, _lenstr(support));
	support = "Display the env shell.\n";
	write(STDOUT_FILENO, support, _lenstr(support));
}

/**
 * setEnv_support_data - gives info for 'setenv' command
 * Return: void
 */

void setEnv_support_data(void)
{
	char *support = "setenv: setenv (const char *id, const char *val,";

	write(STDOUT_FILENO, support, _lenstr(support));
	support = "change)\n\t";
	write(STDOUT_FILENO, support, _lenstr(support));
	support = "put a new environment variable or change the existing one\n";
	write(STDOUT_FILENO, support, _lenstr(support));
}

/**
 * unsetsEnv_support - gives info about 'unsetenv' command
 * Return: void
 */

void unsetsEnv_support(void)
{
	char *support = "unsetenv: unsetenv (const char *id)\n\t";

	write(STDOUT_FILENO, support, _lenstr(support));
	support = "Removes a variable totally from environment\n";
	write(STDOUT_FILENO, support, _lenstr(support));
}

/**
 * close_guide_data - gives support info for 'close' command
 * Return: void
 */

void close_guide_data(void)
{
	char *support = "exit: exit [n]\n Close sh. \n";

	write(STDOUT_FILENO, support, _lenstr(support));
	support = "Closes shell with a status of M. If M is ommited, close";
	write(STDOUT_FILENO, support, _lenstr(support));
	support = "state is of the last command executed\n";
	write(STDOUT_FILENO, support, _lenstr(support));
}

/**
 * supportalias_data - gives info for 'alias' command
 * Return: void
 */

void supportalias_data(void)
{
	char *support = "alias: alias [-p] [name[=val]...]\n";

	write(STDOUT_FILENO, support, _lenstr(support));
	support = "\tShow aliases.\n";
	write(STDOUT_FILENO, support, _lenstr(support));
}
