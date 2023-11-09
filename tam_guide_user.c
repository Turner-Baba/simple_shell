#include "header.h"

/**
 * chdir_guide_info - information on change directory command
 * Return: void
 */

void chdir_guide_info(void)
{
	char *support = "cd: cd [-L |[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, support, _lenstr(support));
	support = "\tSwitch the working directory to.\n ";
	write(STDOUT_FILENO, support, _lenstr(support));
}
/**
 * support_data - gives information on "support" command
 * Return: void
 */

void support_data(void)
{
	char *support = "support: support [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, support, _lenstr(support));
	support = "\tPrint info about builtin commands.\n";
	write(STDOUT_FILENO, support, _lenstr(support));
	support = "Print a short summary of builtin commands.\n";
	write(STDOUT_FILENO, support, _lenstr(support));
}

/**
 * general_help_data - provides support on using support command
 * Return: void
 */

void general_help_data(void)
{
	char *support = "(: TAM, version 1.2(2)-release\n";

	write(STDOUT_FILENO, support, _lenstr(support));
	support = "The commands are defined internally. Type 'support' to see list";
	write(STDOUT_FILENO, support, _lenstr(support));
	support = "Type 'support name' to know more about the function 'id'\n\n";
	write(STDOUT_FILENO, support, _lenstr(support));
	support = " alias: alias [name=['str']]\n";
	write(STDOUT_FILENO, support, _lenstr(support));
	support = " cd: cd [-L|[-P [-e]] [-@]] [dir]\n";
	write(STDOUT_FILENO, support, _lenstr(support));
	support = " exit: exit [n]\n";
	write(STDOUT_FILENO, support, _lenstr(support));
	support = " env: env [option] [id=val] [command [arg]]\n";
	write(STDOUT_FILENO, support, _lenstr(support));
	support = " setenv: setenv [var] [val]\n unsetenV: ";
	write(STDOUT_FILENO, support, _lenstr(support));
	support = " unsetenv: unsetenV {var]\n";
	write(STDOUT_FILENO, support, _lenstr(support));
}
