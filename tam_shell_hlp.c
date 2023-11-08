#include "header.h"
/**
 * exm_envarias - a function that checks for environment var
 * @start: a pointer to the start of the variable
 * @ser: string to be inputed and checked
 * @tam: a pointer to datashell structure
 * Return: (void)
 */
void exm_envarias(vrs_t **start, char *ser, datashell *tam)
{
	int lp, sr, a, val_l;
	char **env_v;

	env_v = tam->envarias;
	for (lp = 0; env_v[lp]; lp++)
	{
		for (a = 1, sr = 0; env_v[lp][sr]; sr++)
		{
			if (env_v[lp][sr] == '=')
			{
				val_l = _lenstr(env_v[lp] + sr + 1);
				append_vrs(start, a, env_v[lp] + sr + 1, val_l);
				return;
			}

			if (ser[a] == env_v[lp][sr])
				a++;
			else
				break;
		}
	}

	for (a = 0; ser[a]; a++)
	{
		if (ser[a] == ' ' || ser[a] == '\t' || ser[a] == ';' || ser[a] == '\n')
			break;
	}

	append_vrs(start, a, NULL, 0);
}

/**
 * handle_uniq_vrs - a function that handles unique variables
 * @start: a pointer to the start of the var
 * @ser: string to be inputed and checked
 * @last: the final position of the shell
 * @tam: a pointer to datashell structure
 * Return: handled characters
 */
int handle_uniq_vrs(vrs_t **start, char *ser, char *last, datashell *tam)
{
	int a, lenght, pdlent;

	lenght = _lenstr(last);
	pdlent = _lenstr(tam->pid);

	for (a = 0; ser[a]; a++)
	{
		if (ser[a] == '$')
		{
			if (ser[a + 1] == '?')
				append_vrs(start, 2, last, lenght), a++;
			else if (ser[a + 1] == '$')
				append_vrs(start, 2, tam->pid, pdlent), a++;
			else if (ser[a + 1] == '\n')
				append_vrs(start, 0, NULL, 0);
			else if (ser[a + 1] == '\0')
				append_vrs(start, 0, NULL, 0);
			else if (ser[a + 1] == ' ')
				append_vrs(start, 0, NULL, 0);
			else if (ser[a + 1] == '\t')
				append_vrs(start, 0, NULL, 0);
			else if (ser[a + 1] == ';')
				append_vrs(start, 0, NULL, 0);
			else
				exm_envarias(start, ser + a, tam);
		}
	}

	return (a);

}

/**
 * string_sub_vrs - a function that substitutes substrings in a str with var
 * @start: a pointer to the start of the var
 * @ser: the inputed string
 * @nser: new string
 * @nlong: the length of new string
 * Return: a pointer to the new string
 */
char *string_sub_vrs(vrs_t **start, char *ser, char *nser, int nlong)
{
	int a, b, c;
	vrs_t *id;

	id = *start;
	for (b = a = 0; a < nlong; a++)
	{
		if (ser[b] == '$')
		{
			if (!(id->vrlen) && !(id->vlen))
			{
				nser[a] = ser[b];
				b++;
			}

			else if (id->vrlen && !(id->vlen))
			{
				for (c = 0; c < id->vrlen; c++)
					b++;
				a--;
			}
			else
			{
				for (c = 0; c < id->vlen; c++)
				{
					nser[a] = id->val[c];
					a++;
				}
				b += (id->vrlen);
				a--;
			}
			id = id->subsqt;
		}
		else
		{
			nser[a] = ser[b];
			b++;
		}
	}

	return (nser);
}

/**
 * vrs_string_swap - a function that swaps variables
 * @ser: the string to be swaped
 * @tam: a pointer to datashell structure
 * Return: a pointer to the swaped string
 */
char *vrs_string_swap(char *ser, datashell *tam)
{
	vrs_t *start, *id;
	char *cd, *nser;
	int lento, lent_n;

	cd = string_fmt(tam->position);
	start = NULL;
	lento = handle_uniq_vrs(&start, ser, cd, tam);
	if (start == NULL)
	{
		free(cd);
		return (ser);
	}

	id = start;
	lent_n = 0;
	while (id != NULL)
	{
		lent_n += (id->vlen - id->vrlen);
		id = id->subsqt;
	}

	lent_n += lento;
	nser = malloc(sizeof(char) * (lent_n + 1));
	nser[lent_n] = '\0';
	nser = string_sub_vrs(&start, ser, nser, lent_n);

	free(ser);
	free(cd);
	clear_vrs(&start);

	return (nser);
}

/**
 * execute_path - a function that executes path
 * @cmnd: command to be located for execution
 * @envarias: environment var
 * Return: path of the command
 */
char *execute_path(char *cmnd, char **envarias)
{
	char *d_path, *p, *tkp, *directory;
	int dir_l, l_cmnd, a;
	struct stat ps;

	d_path = getenV_("PATH", envarias);
	if (d_path)
	{
		p = dup_string(d_path);
		l_cmnd = _lenstr(cmnd);
		tkp = tok_string(p, ":");
		a = 0;
		while (tkp != NULL)
		{
			if (exm_currdir(d_path, &a))
				if (stat(cmnd, &ps) == 0)
					return (cmnd);
			dir_l = _lenstr(tkp);
			directory = malloc(dir_l + l_cmnd + 2);
			cpy_string(directory, tkp);
			str_concat(directory, "/");
			str_concat(directory, cmnd);
			str_concat(directory, "\0");

			if (stat(directory, &ps) == 0)
			{
				free(p);
				return (directory);
			}
			free(directory);
			tkp = tok_string(NULL, ":");
		}
		free(p);
		if (stat(cmnd, &ps) == 0)
			return (cmnd);
		return (NULL);
	}
	if (cmnd[0] == '/')
		if (stat(cmnd, &ps) == 0)
			return (cmnd);
	return (NULL);
}
