#include "header.h"
/**
 * opens_sh - a function that executes shell
 * @tam: a pointer to datashell structure
 * Return: void
 */
void opens_sh(datashell *tam)
{
	int its_eof, sh = 1;
	char *code;

	while (sh == 1)
	{
		write(STDIN_FILENO, ":> ", 3);
		code = exam_user_data(&its_eof);
		if (its_eof != -1)
		{
			code = remove_coms(code);
			if (code == NULL)
				continue;
			if (verify_error(tam, code) == 1)
			{
				tam->position = 2;
				free(code);
				continue;
			}

			code = vrs_string_swap(code, tam);
			sh = delim_cdline(tam, code);
			tam->ln_index += 1;
			free(code);
		}

		else
		{
			sh = 0;
			free(code);
		}
	}
}

/**
 * _subsqt_lst - a function that moves subsequently to nect command line
 * @div_lst: a pointer to the divider list
 * @cdline_lst: a pointer to the cdline list
 * @tam: a pointer to datashell structure
 * Return: void
 */
void _subsqt_lst(divd_t **div_lst, cdline_t **cdline_lst, datashell *tam)
{
	int sh = 1;
	divd_t *div;
	cdline_t *cdline;

	div = *div_lst;
	cdline = *cdline_lst;

	while (div != NULL && sh)
	{
		if (tam->position == 0)
		{
			if (div->divider == '&' || div->divider == ';')
				sh = 0;
			if (div->divider == '|')
				cdline = cdline->subsqt, div = div->subsqt;
		}

		else
		{
			if (div->divider == '|' || div->divider == ';')
				sh = 0;
			if (div->divider == '&')
				cdline = cdline->subsqt, div = div->subsqt;
		}

		if (div != NULL && !sh)
			div = div->subsqt;
	}
	*div_lst = div;
	*cdline_lst = cdline;
}

/**
 * exm_currdir - a function that checks for current directory
 * @way: a pointer to char
 * @indx: a pointer to int
 * Return: 0
 */
int exm_currdir(char *way, int *indx)
{
	if (way[*indx] == ':')
		return (0);
	while (way[*indx] != ':' && way[*indx])
	{
		*indx += 1;
	}

	if (way[*indx])
		*indx += 1;
	return (1);
}

/**
 * exm_execc - a function that examines executable files
 * @tam: a pointer to datashell struct
 * Return: num of chars in filename
 */
int exm_execc(datashell *tam)
{
	struct stat ps;
	int a;
	char *input;

	input = tam->arg_tok[0];
	for (a = 0; input[a]; a++)
	{
		if (input[a] == '.')
		{
			if (input[a + 1] == '.')
				return (0);
			if (input[a + 1] == '/')
				continue;
			else
				break;
		}

		else if (input[a] == '/' && a != 0)
		{
			if (input[a + 1] == '.')
				continue;
			a++;
			break;
		}
		else
			break;
	}
	if (a == 0)
		return (0);
	if (stat(input + a, &ps) == 0)
	{
		return (a);
	}
	find_err(tam, 127);
	return (-1);
}

/**
 * exm_perm - a function that checks for permission
 * @path: dir to check permission
 * @tam: a pointer to datashell
 * Return: 0 on success
 */
int exm_perm(char *path, datashell *tam)
{
	if (path == NULL)
	{
		find_err(tam, 127);
		return (1);
	}

	if (cmp_string(tam->arg_tok[0], path) != 0)
	{
		if (access(path, X_OK) == -1)
		{
			find_err(tam, 126);
			free(path);
			return (1);
		}

		free(path);
	}

	else
	{
		if (access(tam->arg_tok[0], X_OK) == -1)
		{
			find_err(tam, 126);
			return (1);
		}
	}

	return (0);
}
