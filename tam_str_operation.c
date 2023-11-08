#include "header.h"
/**
 * _lenstr - a function that gets te length of a string
 * @ser: a pointer to string
 * Return: the lent of the string
 */
int _lenstr(const char *ser)
{
	int lenght;

	for (lenght = 0; ser[lenght] != '\0'; lenght++)
	{
	}

	return (lenght);
}

/**
 * str_concat - a function that concatenates string together
 * @dest: a pointer to the string to concatenate to
 * @frm: a pointer to the source string
 * Return: a pointer to the dest string
 */
char *str_concat(char *dest, const char *frm)
{
	int a = 0;
	int b = 0;

	while (dest[a] != '\0')
	{
		a++;
	}

	while (frm[b] != '\0')
	{
		dest[a] = frm[b];
		a++;
		b++;
	}

	dest[a] = '\0';
	return (dest);
}

/**
 * cmp_string - a function that actually compares two strings
 * @ser1: a pointer to the 1st string
 * @ser2: a pointer to the 2nd string
 * Return: (0) on success
 */
int cmp_string(char *ser1, char *ser2)
{
	int a = 0;

	while (ser1[a] == ser2[a] && ser1[a] != '\0')
	{
		a++;
	}

	if (ser1[a] > ser2[a])
		return (1);
	if (ser1[a] < ser2[a])
		return (-1);
	return (0);
}

/**
* chr_string - a function that finds first occurrence of a char in a string
* @ser: a pointer to the string to be searched
* @ltr: chars to locate
* Return: a pointer to occurence of @ltr in ser
*/
char *chr_string(char *ser, char ltr)
{
	unsigned int a = 0;

	for (; *(ser + a) != '\0'; a++)
	{
		if (*(ser + a) == ltr)
		{
			return (ser + a);
		}
	}

	if (*(ser + a) == ltr)
		return (ser + a);
	return ("\0");
}
