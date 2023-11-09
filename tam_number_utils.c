#include "header.h"

/**
 * count_num - counts length number
 * @count: Numeric value to ascertain its length
 * Return: length of given num
 */

int count_num(int count)
{
	unsigned int c;
	int length = 1;

	if (count < 0)
	{
		length++;
		c = count * -1;
	}
	else
	{
		c = count;
	}
	while (c > 9)
	{
		length++;
		c = c / 10;
	}
	return (length);
}
/**
 * string_fmt - converts int to str
 * @count: integer to be converted
 * Return: Allocated string representing the number with flexibility
 */

char *string_fmt(int count)
{
	unsigned int c;
	int length = count_num(count);
	char *buffs;

	buffs = malloc(sizeof(char) * (length + 1));
	if (buffs == 0)
		return (NULL);
	*(buffs + length) = '\0';
	if (count < 0)
	{
		c = count * -1;
		buffs[0] = '-';
	}
	else
	{
		c = count;
	}
	length--;
	do {
		*(buffs + length) = (c % 10) + '0';
		c = c / 10;
		length--;
	}
	while (c > 0)
		;
	return (buffs);
}

/**
 * str_atoi - converts str to int
 * @ser: string to be converted
 * Return: Parsing the string yields an integer value
 */

int str_atoi(char *ser)
{
	unsigned int aa = 0, cd = 0, rest = 0, mark = 1, times = 1, indx;

	while (*(ser + aa) != '\0')
	{
		if (cd > 0 && (*(ser + aa) < 48 || *(ser + aa) > 57))
			break;
		if (*(ser + aa) == '-')
			mark *= -1;
		if ((*(ser + aa) >= 48) && (*(ser + aa) <= 57))
		{
			if (cd > 0)
				times *= 10;
			cd++;
		}
	}
	for (indx = aa - cd; indx < aa; indx++)
	{
		rest = rest + ((*(ser + indx) - 48) * times);
		times /= 10;
	}
	return (rest * mark);
}
