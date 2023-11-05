#include "header.h"

/**
 * handle_error - handles errors
 * @ser: string input
 * @indx: index to be checked
 * @lchars: last character handled in the string
 * Return: indx where the error is seen
 */

int handle_error(char *ser, int indx, char lchars)
{
	int digit = 0;

	if (*ser == '\0')
		return (0);
	if (*ser == ' ' || *ser == '\t')
		return (handle_error(ser + 1, indx + 1, lchars));
	if (*ser == ';')
	{
		if (lchars == '|' || lchars == '&' || lchars == ';')
			return (indx);
	}
	if (*ser == '|')
	{
		if (lchars == ';' || lchars == '&')
			return (indx);
		if (lchars == '|')
		{
			digit = chars_count(ser, 0);
			if (digit == 0 || digit > 1)
				return (indx);
		}
	}
	if (*ser == '&')
	{
		if (lchars == ';' || lchars == '|')
			return (indx);
		if (lchars == '&')
		{
			digit = chars_count(ser, 0);
			if (digit == 0 || digit > 1)
				return (indx);
		}
	}
	return (handle_error(ser + 1, indx + 1, *ser));
}

/**
 * _printerror - outputs message error if syntax error is seen
 * @tam: shell data structure
 * @ser: string input to be verified
 * @indx: position where eror will be seen
 * @errctr: flag ctrl for message rror
 * Return: void
 */

void _printerror(datashell *tam, char *ser, int indx, int errctr)
{
	char *emsg, *errmsg, *mgerr, *err, *cnter;
	int length;

	if (ser[indx] == ';')
	{
		if (errctr == 0)
			emsg = (ser[indx + 1] == ';' ? ";;" : ";");
		else
			emsg = (ser[indx - 1] == ';' ? ";;" : ";");
	}
	if (ser[indx] == '|')
		emsg = (ser[indx + 1] == '|' ? "||" : "|");
	if (ser[indx] == '&')
		emsg = (ser[indx + 1] == '&' ? "&&" : "&");
	errmsg = ": Syntax ERROR: \"";
	mgerr = "\" not expected\n";
	cnter = string_fmt(tam->ln_index);
	length = _lenstr(tam->argv[0]) + _lenstr(cnter);
	length += _lenstr(emsg) + _lenstr(errmsg) + _lenstr(mgerr) + 2;
	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(cnter);
		return;
	}
	cpy_string(err, tam->argv[0]);
	str_concat(err, ": ");
	str_concat(err, cnter);
	str_concat(err, errmsg);
	str_concat(err, emsg);
	str_concat(err, mgerr);
	str_concat(err, "\0");
	write(STDERR_FILENO, err, length);
	free(err);
	free(cnter);
}

/**
 * verify_error - mediator function to identify and display syntax error
 * @tam: pointer to data structure
 * @ser: string input to be looked into
 * Return: 1 if syntax error is found, 0 if not found
 */

int verify_error(datashell *tam, char *ser)
{
	int indx = 0;
	int funcchar = 0;
	int c = 0;

	funcchar = indx_chars(ser, &indx);
	if (funcchar == -1)
	{
		_printerror(tam, ser, indx, 0);
		return (1);
	}
	c = handle_error(ser + indx, 0, *(ser + indx));
	if (c != 0)
	{
		_printerror(tam, ser, indx + c, 1);
		return (1);
	}
	return (0);
}

/**
 * unify_error - displays message for a command error
 * @tam: pointer to data structure
 * @emsg: print messge
 * @err: print err message
 * @cd_ctrl: counts lines as string
 * Return: err mesage
 */

char *unify_error(datashell *tam, char *emsg, char *err, char *cd_ctrl)
{
	char *option;

	cpy_string(err, tam->argv[0]);
	str_concat(err, "; ");
	str_concat(err, cd_ctrl);
	str_concat(err, ": ");
	str_concat(err, tam->arg_tok[0]);
	str_concat(err, emsg);
	if (tam->arg_tok[1][0] == '-')
	{
		option = malloc(3);
		option[0] = '-';
		option[1] = tam->arg_tok[1][1];
		option[2] = '\0';
		str_concat(err, option);
		free(option);
	}
	else
	{
		str_concat(err, tam->arg_tok[1]);
	}
	str_concat(err, "\n");
	str_concat(err, "\0");
	return (err);
}
