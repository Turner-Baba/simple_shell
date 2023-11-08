#include "header.h"
/**
 * exam_user_data - a function that reads inputs from STDIO
 * @its_eof: a pointer to store return val
 * Return: a pointer to the input string
 */
char *exam_user_data(int *its_eof)
{
	char *ser = NULL;
	size_t bsize = 0;

	*its_eof = _getline_(&ser, &bsize, stdin);
	return (ser);
}

/**
 * letter_swap - a function that swaps characters
 * @ser: the string
 * @sub: substitutes
 * Return: a pointer to the substituted string
 */
char *letter_swap(char *ser, int sub)
{
	int a;

	if (sub == 0)
	{
		for (a = 0; ser[a]; a++)
		{
			if (ser[a] == '|')
			{
				if (ser[a + 1] != '|')
					ser[a] = 16;
				else
					a++;
			}

			if (ser[a] == '&')
			{
				if (ser[a + 1] != '&')
					ser[a] = 12;
				else
					a++;
			}
		}
	}

	else
	{
		for (a = 0; ser[a]; a++)
		{
			ser[a] = (ser[a] == 16 ? '|' : ser[a]);
			ser[a] = (ser[a] == 12 ? '&' : ser[a]);
		}
	}

	return (ser);
}

/**
 * delim_cdline - a function that divides command lines
 * @tam: a pointer to datashell structure
 * @ser: string wwith command
 * Return: (0) to leave loop or (1) to continue loop
 */
int delim_cdline(datashell *tam, char *ser)
{
	divd_t *div_start, *div_lst;
	cdline_t *cdline_start, *cdline_lst;
	int indx;

	div_start = NULL;
	cdline_start = NULL;
	append_nodes_list(&div_start, &cdline_start, ser);
	div_lst = div_start;
	cdline_lst = cdline_start;

	while (cdline_lst != NULL)
	{
		tam->cdline = cdline_lst->ln;
		tam->arg_tok = data_parse(tam->cdline);
		indx = handles_cmnd(tam);
		free(tam->arg_tok);
		if (indx == 0)
			break;
		_subsqt_lst(&div_lst, &cdline_lst, tam);
		if (cdline_lst != NULL)
			cdline_lst = cdline_lst->subsqt;
	}

	clear_div(&div_start);
	clear_cdline(&cdline_start);
	if (indx == 0)
		return (0);
	return (1);
}

/**
 * data_parse - a function that parses input string
 * @ser: string to be parsed
 * Return: tokenized string
 */
char **data_parse(char *ser)
{
	size_t bufsize, indx;
	char **parse;
	char *parsed;

	bufsize = TOK_SIZE;
	parse = malloc(sizeof(char *) * (bufsize));
	if (parse == NULL)
	{
		write(STDERR_FILENO, ": cannot allocate\n", 17);
		exit(EXIT_FAILURE);
	}

	parsed = tok_string(ser, TOK_SEP);
	parse[0] = parsed;
	for (indx = 1; parsed != NULL; indx++)
	{
		if (indx == bufsize)
		{
			bufsize += TOK_SIZE;
			parse = _re_alloc_ptr(parse, indx, sizeof(char *) * bufsize);
			if (parse == NULL)
			{
				write(STDERR_FILENO, ": cannot allocate\n", 17);
				exit(EXIT_FAILURE);
			}
		}

		parsed = tok_string(NULL, TOK_SEP);
		parse[indx] = parsed;
	}

	return (parse);
}

/**
 * remove_coms - a function that removes comments
 * @stat: string to delete comments from
 * Return: string after removing comments
 */
char *remove_coms(char *stat)
{
	int a, digits = 0;

	for (a = 0; stat[a]; a++)
	{
		if (stat[a] == '#')
		{
			if (a == 0)
			{
				free(stat);
				return (NULL);
			}

			if (stat[a - 1] == ' ' || stat[a - 1] == '\t' || stat[a - 1] == ';')
				digits = a;
		}
	}

	if (digits != 0)
	{
		stat = _re_alloc(stat, a, digits + 1);
		stat[digits] = '\0';
	}

	return (stat);
}
