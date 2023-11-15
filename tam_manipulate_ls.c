#include "header.h"
/**
 * append_div - appens a different node to the finish line of linked list
 * @start: pointer to head of linked list
 * @div: divider char to be included <;|&)
 * Return: mem address of updaated head of linked list
 */

divd_t *append_div(divd_t **start, char div)
{
	divd_t *nnde, *temp;

	nnde = malloc(sizeof(divd_t));
	if (nnde == NULL)
		return (NULL);
	nnde->divider = div;
	nnde->subsqt = NULL;
	temp = *start;
	if (temp == NULL)
		*start = nnde;
	else
	{
		while (temp->subsqt != NULL)
			temp = temp->subsqt;
		temp->subsqt = nnde;
	}
	return (*start);
}

/**
 * append_cdline - adds to the command line
 * @start: pointer to head of linked list
 * @line: line
 * Return: memory address of updated head of linked list
 */

cdline_t *append_cdline(cdline_t **start, char *line)
{
	cdline_t *nnde, *temp;

	nnde = malloc(sizeof(cdline_t));
	if (nnde == NULL)
		return (NULL);
	nnde->ln = line;
	nnde->subsqt = NULL;
	temp = *start;
	if (temp == NULL)
	{
		*start = nnde;
	}
	else
	{
		while (temp->subsqt != NULL)
			temp = temp->subsqt;
		temp->subsqt = nnde;
	}
	return (*start);
}

/**
 * append_vrs - appends var at the end of linked list
 * @start: pointer to head of linked list
 * @varlen: variable length
 * @valu: variable value
 * @valength: variable length
 * Return: memory address of updated head of linked list
 */

vrs_t *append_vrs(vrs_t **start, int varlen, char *valu, int valength)
{
	vrs_t *nnde, *temp;

	nnde = malloc(sizeof(vrs_t));
	if (nnde == NULL)
		return (NULL);
	nnde->vrlen = varlen;
	nnde->val = valu;
	nnde->vlen = valength;
	nnde->subsqt = NULL;
	temp = *start;
	if (temp == NULL)
	{
		*start = nnde;
	}
	else
	{
		while (temp->subsqt != NULL)
			temp = temp->subsqt;
		temp->subsqt = nnde;
	}
	return (*start);
}
/**
 * append_nodes_list - appends divider and cdline to linked lists
 * @div_start: pointer to head of divider linked list
 * @cdline_start: pointer to head of linked list
 * @ser: string input
 * Return: void
 */

void append_nodes_list(divd_t **div_start, cdline_t **cdline_start, char *ser)
{
	int c;
	char *line;

	ser = letter_swap(ser, 0);
	for (c = 0; ser[c]; c++)
	{
		if (ser[c] == ';')
			append_div(div_start, ser[c]);
		if (ser[c] == '|' || ser[c] == '&')
		{
			append_div(div_start, ser[c]);
			c++;
		}
	}
	line = tok_string(ser, ";|&");
	do {
		line = letter_swap(line, 1);
		append_cdline(cdline_start, line);
		line = tok_string(NULL, ";|&");
	} while (line != NULL);
}
