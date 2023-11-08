#include "header.h"
/**
 * dup_string - a function that duplicates a string
 * @ser: a pointer to the string to be duplicated
 * Return: pointer to the string duplicated
 */
char *dup_string(const char *ser)
{
	char *stringdup;
	size_t lenght;

	lenght = _lenstr(ser);
	stringdup = malloc(sizeof(char) * (lenght + 1));

	if (!stringdup)
		return (NULL);
	memory_cp(stringdup, ser, lenght + 1);
	return (stringdup);
}

/**
 * rev_string - a function that reverses a string
 * @ser: a pointer to the string to be reversed
 * Return: (void)
 */
void rev_string(char *ser)
{
	int a, b;
	int lenght = 0;
	char *stringn, tpm;

	while (lenght >= 0)
	{
		if (ser[lenght] == '\0')
			break;
		lenght++;
	}

	stringn = ser;
	for (a = 0; a < (lenght - 1); a++)
	{
		for (b = a + 1; b > 0; b--)
		{
			tpm = *(stringn + b);
			*(stringn + b) = *(stringn + (b - 1));
			*(stringn + (b - 1)) = tpm;
		}
	}
}

/**
 * sspn_string - a function that gets the length of a substring
 * @ser: the string to check
 * @ltr: chars to to check for in the prefix
 * Return: total number of matchng numbers ser that are in ltr
 */
int sspn_string(char *ser, char *ltr)
{
	int a, b, bytess;

	for (a = 0; ser[a] != '\0'; a++)
	{
		bytess = 1;
		for (b = 0; ltr[b] != '\0'; b++)
		{
			if (ser[a] == ltr[b])
			{
				bytess = 0;
				break;
			}
		}

		if (bytess == 1)
			break;
	}

	return (a);
}

/**
 * tok_string - a function that tokenize a string by some dividers
 * @ser: the string to be tokenized
 * @div: dividers to be used
 * Return: a pointer to subsequents token
 */
char *tok_string(char ser[], const char *div)
{
	static char *cposition, *str_end;
	char *string_start;
	unsigned int a, bytess;

	if (ser != NULL)
	{
		if (cmp_chars(ser, div))
			return (NULL);
		cposition = ser;
		a = _lenstr(ser);
		str_end = &ser[a];
	}

	string_start = cposition;
	if (string_start == str_end)
		return (NULL);
	for (bytess = 0; *cposition; cposition++)
	{
		if (cposition != string_start)
			if (*cposition && *(cposition - 1) == '\0')
				break;
		for (a = 0; div[a]; a++)
		{
			if (*cposition == div[a])
			{
				*cposition = '\0';
				if (cposition == string_start)
					string_start++;
				break;
			}
		}

		if (bytess == 0 && *cposition)
			bytess = 2;
	}

	if (bytess == 0)
		return (NULL);
	return (string_start);
}

/**
 * cpy_string - a function that copie string from one place to another
 * @dest: a pointer to dest string
 * @frm: a pointer to the string to be copied
 * Return: a pointer to dest string after it has been copied
 */
char *cpy_string(char *dest, char *frm)
{
	size_t a;

	for (a = 0; frm[a] != '\0'; a++)
	{
		dest[a] = frm[a];
	}

	dest[a] = '\0';
	return (dest);
}
