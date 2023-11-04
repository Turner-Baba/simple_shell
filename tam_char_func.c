#include "header.h"
/**
 * _number - a function that shos if an input string is a number
 * @ser: input string
 * Return: (1) if string, (0) if otherwise
 */
int _number(const char *ser)
{
	unsigned int a;

	for (a = 0; ser[a]; a++)
	{
		if (ser[a] < '0' || ser[a] > '9')
			return (0);
	}

	return (1);
}

/**
 * cmp_chars - a function that compares characters
 * @ser: string
 * @div: divider
 * Return: 1 if char matches otherwise return 0
 */
int cmp_chars(char ser[], const char *div)
{
	unsigned int a, b, c;

	for (a = 0, c = 0; ser[a]; a++)
	{
		for (b = 0; div[b]; b++)
		{
			if (ser[a] == div[b])
			{
				c++;
				break;
			}
		}
	}

	if (a == c)
		return (1);
	return (0);
}

/**
 * chars_count - a function that counts how many times a char was repeated
 * @ser: string to be counted
 * @indx: string index
 * Return: num of repetition of characters
 */
int chars_count(char *ser, int indx)
{
	if (*(ser - 1) == *ser)
		return (chars_count(ser - 1, indx + 1));

	return (indx);
}

/**
 * indx_chars - a function that finds non-whitespace character
 * @ser: string to check
 * @indx: a pointer
 * Return: 1 if error occurs, otherwise return 0
 */
int indx_chars(char *ser, int *indx)
{
	for (*indx = 0; ser[*indx]; *indx += 1)
	{
		if (ser[*indx] == ' ' || ser[*indx] == '\t')
			continue;
		if (ser[*indx] == ';' || ser[*indx] == '|' || ser[*indx] == '&')
			return (-1);
		break;
	}

	return (0);
}
