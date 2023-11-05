#include "header.h"

/**
 * path_error - produces error message for chdir command
 * @tam: pointer to dat struct
 * Return: pointer to error message
 */

char *path_error(datashell *tam)
{
	int length, idlength;
	char *err, *cd_ctrl, *emsg;

	cd_ctrl = string_fmt(tam->ln_index);
	if (tam->arg_tok[1][0] == '-')
	{
		emsg = ": Not acceptable option ";
		idlength = 2;
	}
	else
	{
		emsg = ": unable to move to directory ";
		idlength = _lenstr(tam->arg_tok[1]);
	}
	length = _lenstr(tam->argv[0]) + _lenstr(tam->arg_tok[0]);
	length += _lenstr(cd_ctrl) + _lenstr(emsg) + idlength + 5;
	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(cd_ctrl);
		return (NULL);
	}
	err = unify_error(tam, emsg, err, cd_ctrl);
	free(cd_ctrl);
	return (err);
}

/**
 * cmd_invalid - produces error message fr a comand not found
 * @tam: a pointer to data struct
 * Return: pointer to data struct
 */

char *cmd_invalid(datashell *tam)
{
	int length;
	char *err, *cd_ctrl;

	cd_ctrl = string_fmt(tam->ln_index);
	length = _lenstr(tam->argv[0]) + _lenstr(cd_ctrl);
	length += _lenstr(tam->arg_tok[0]) + 16;
	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(err);
		free(cd_ctrl);
		return (NULL);
	}
	cpy_string(err, tam->argv[0]);
	str_concat(err, ": ");
	str_concat(err, cd_ctrl);
	str_concat(err, ": ");
	str_concat(err, tam->arg_tok[0]);
	str_concat(err, ": Unable to find\n");
	str_concat(err, "\0");
	free(cd_ctrl);
	return (err);
}

/**
 * exit_shell_error - exits shell error message
 * @tam: pointer to data structure
 * Return: poiinter to the rror message
 */

char *exit_shell_error(datashell *tam)
{
	int length;
	char *err, *cd_ctrl;

	cd_ctrl = string_fmt(tam->ln_index);
	length = _lenstr(tam->argv[0]) + _lenstr(cd_ctrl);
	length += _lenstr(tam->arg_tok[0]) + _lenstr(tam->arg_tok[1]) + 23;
	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(cd_ctrl);
		return (NULL);
	}
	cpy_string(err, tam->argv[0]);
	str_concat(err, ": ");
	str_concat(err, cd_ctrl);
	str_concat(err, ": ");
	str_concat(err, tam->arg_tok[0]);
	str_concat(err, ": number not allowed: ");
	str_concat(err, tam->arg_tok[1]);
	str_concat(err, "\n\0");
	free(cd_ctrl);
	return (err);
}

/**
 * settings_emsg - poduce 'env' command error message
 * @tam: pointer to data structure
 * Return: err message
 */

char *settings_emsg(datashell *tam)
{
	int length;
	char *err, *cd_ctrl, *emsg;

	cd_ctrl = string_fmt(tam->ln_index);
	emsg = ": could not remove or add from environment\n";
	length = _lenstr(tam->argv[0]) + _lenstr(cd_ctrl);
	length += _lenstr(tam->arg_tok[0]) + _lenstr(emsg) + 4;
	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(err);
		free(cd_ctrl);
		return (NULL);
	}
	cpy_string(err, tam->argv[0]);
	str_concat(err, ": ");
	str_concat(err, cd_ctrl);
	str_concat(err, ": ");
	str_concat(err, tam->arg_tok[0]);
	str_concat(err, emsg);
	str_concat(err, "\0");
	free(cd_ctrl);

	return (err);
}

/**
 * path126_emsg - prints path command error message
 * @tam: pointer to data struct
 * Return: messgae error
 */

char *path126_emsg(datashell *tam)
{
	int length;
	char *cd_ctrl, *err;

	cd_ctrl = string_fmt(tam->ln_index);
	length = _lenstr(tam->argv[0]) + _lenstr(cd_ctrl);
	length += _lenstr(tam->arg_tok[0]) + 24;
	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(err);
		free(cd_ctrl);
		return (NULL);
	}
	cpy_string(err, tam->argv[0]);
	str_concat(err, ": ");
	str_concat(err, cd_ctrl);
	str_concat(err, ": ");
	str_concat(err, tam->arg_tok[0]);
	str_concat(err, ": Not permitted\n");
	str_concat(err, "\0");
	free(cd_ctrl);
	return (err);
}
