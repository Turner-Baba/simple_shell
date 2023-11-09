#include "header.h"

/**
 * memory_cp - copies info from one mem point to another
 * @dest: mem point to copy to
 * @frm: src mem point to copy from
 * @dimen: simension number of bytes to copy
 * Return: void
 */

void memory_cp(void *dest, const void *frm, unsigned int dimen)
{
	char *chars_dest = (char *)dest;
	const char *chars_frm = (const char *)frm;
	unsigned int c;

	for (c = 0; c < dimen; c++)
		chars_dest[c] = chars_frm[c];
}

/**
 * _re_alloc - reallocates mem for block of input
 * @b: pointer to memory block to be reallocated
 * @prv_dimen: previously located memory size
 * @nw_dimen: updated memory size
 * Return: pointer to updated memory block
 */

void *_re_alloc(void *b, unsigned int prv_dimen, unsigned int nw_dimen)
{
	void *uptr = NULL;

	if (b == NULL)
		return (malloc(nw_dimen));
	if (nw_dimen == 0)
	{
		free(b);
		return (NULL);
	}
	if (nw_dimen == prv_dimen)
		return (b);
	uptr = malloc(nw_dimen);
	if (uptr == NULL)
		return (NULL);
	if (nw_dimen < prv_dimen)
		memory_cp(uptr, b, nw_dimen);
	else
		memory_cp(uptr, b, prv_dimen);
	free(b);
	return (uptr);
}

/**
 * _re_alloc_ptr - Adjusts memory for an array of double pointers
 * @b: Array of pointers with a double pointer
 * @prv_dimen: Previous allocated array size in bytes
 * @nw_dimen: Updated array size in bytes
 * Return: pointer to Freshly allocated array of pointers
 */

char **_re_alloc_ptr(char **b, unsigned int prv_dimen, unsigned int nw_dimen)
{
	char **cptr;
	unsigned int c;

	if (b == NULL)
		return (malloc(sizeof(char *) * nw_dimen));
	if (nw_dimen == prv_dimen)
		return (b);
	cptr = malloc(sizeof(char *) * nw_dimen);
	if (cptr == NULL)
		return (NULL);
	for (c = 0; c < prv_dimen; c++)
		cptr[c] = b[c];
	free(b);
	return (cptr);
}
