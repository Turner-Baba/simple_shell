#include "header.h"

/**
 * envarias_comp - checks an environ variable with name inputed
 * @envid : environment id
 * @id: id inputed to compare
 * Return: 0 if successfull
 */

int envarias_comp(const char *envid, const char *id)
{
	int c;

	for (c = 0; envid[c] != '='; c++)
	{
		if (envid[c] != id[c])
		{
			return (0);
		}
	}
	return (c + 1);
}

/**
 * dup_env_stat - duplicates info for a new variable
 * @id: id of environment var
 * @sig: val of environ var
 * Return: new environ variable
 */

char *dup_env_stat(char *id, char *sig)
{
	char *cenv;
	int lid, lensig, length;

	lid = _lenstr(id);
	lensig = _lenstr(sig);
	length = lid + lensig + 2;
	cenv = malloc(sizeof(char) * (length));
	cpy_string(cenv, id);
	str_concat(cenv, "=");
	str_concat(cenv, sig);
	str_concat(cenv, "\0");

	return (cenv);
}

/**
 * _setenV_ - sets the val of environment variable or make a new
 * one if it is not available
 * @tam: pointer to data struct
 * Return: 0 on success
 */

int _setenV_(datashell *tam)
{
	if (tam->arg_tok[1] == NULL || tam->arg_tok[2] == NULL)
	{
		find_err(tam, -1);
		return (1);
	}
	set_enV_(tam->arg_tok[1], tam->arg_tok[2], tam);
	return (0);
}

/**
 * output_lines - outputs lines
 * @ptr: pounter to buffer that keeps string input
 * @lndimen: mass of the ptr buffer
 * @buffs: string put to ptr
 * @buff_size: size of buffer
 * Return: void
 */

void output_lines(char **ptr, size_t *lndimen, char *buffs, size_t buff_size)
{
	if (*ptr == NULL)
	{
		if (buff_size > BSIZE)
			*lndimen = buff_size;
		else
			*lndimen = BSIZE;
		*ptr = buffs;
	}
	else if (*lndimen < buff_size)
	{
		if (buff_size > BSIZE)
			*lndimen = buff_size;
		else
			*lndimen = BSIZE;
		*ptr = buffs;
	}
	else
	{
		cpy_string(*ptr, buffs);
		free(buffs);
	}
}

/**
 * _getline_ - gets input
 * @ptr: pointer to buffer that keeps inputs
 * @lndimen: pointer to mass of ptr
 * @curr: current to chck from
 * Return: no of byte read from input
 */

ssize_t _getline_(char **ptr, size_t *lndimen, FILE *curr)
{
	int c;
	static ssize_t ser;
	ssize_t byte;
	char *buffs;
	char numchar  = 'z';

	if (ser == 0)
		fflush(curr);
	else
		return (-1);
	ser = 0;
	buffs = malloc(sizeof(char) * BSIZE);
	if (buffs == 0)
		return (-1);
	while (numchar != '\n')
	{
		c = read(STDIN_FILENO, &numchar, 1);
		if (c == -1 || (c == 0 && ser == 0))
		{
			free(buffs);
			return (-1);
		}
		if (c == 0 && ser != 0)
		{
			ser++;
			break;
		}
		if (ser >= BSIZE)
			buffs = _re_alloc(buffs, ser, ser + 1);
		buffs[ser] = numchar;
		ser++;
	}
	buffs[ser] = '\0';
	output_lines(ptr, lndimen, buffs, ser);
	byte = ser;
	if (c != 0)
		ser = 0;
	return (byte);
}
