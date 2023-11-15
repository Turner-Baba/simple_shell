#include "header.h"

/**
 * clear_div - clears the divd list and its points
 * @start: pointer to the start of linked list
 * Return: void
 */

void clear_div(divd_t **start)
{
	divd_t *temp;
	divd_t *point;

	if (start != NULL)
	{
		point = *start;
		while ((temp = point) != NULL)
		{
			point = point->subsqt;
			free(temp);
		}
		*start = NULL;
	}
}

/**
 * clear_cdline - frees command line ls and points
 * @start: pointer to start of linked list
 * Return: void
 */

void clear_cdline(cdline_t **start)
{
	cdline_t *temp;
	cdline_t *point;

	if (start != NULL)
	{
		point = *start;
		while ((temp = point) != NULL)
		{
			point = point->subsqt;
			free(temp);
		}
		*start = NULL;
	}
}

/**
 * clear_vrs - frees variable list and its option
 * @start: pointer to head of linked list
 * Return: void
 */

void clear_vrs(vrs_t **start)
{
	vrs_t *temp;
	vrs_t *point;

	if (start != NULL)
	{
		point = *start;
		while ((temp = point) != NULL)
		{
			point = point->subsqt;
			free(temp);
		}
		*start = NULL;
	}
}
