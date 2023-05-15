#include "ashell.h"

/**
 * _memcpy - To copies information between void pointers.
 * @nptr: Destination pointer.
 * @ptr: Source pointer.
 * @size: Size of the new pointer.
 *
 * Return: no return.
 */
void _memcpy(void *nptr, const void *ptr, unsigned int size)
{
	char *char_pt = (char *)ptr;
	char *char_newpt = (char *)nptr;
	unsigned int n;

	for (n = 0; n < size; n++)
		char_newpt[n] = char_pt[n];
}

/**
 * _realloc - To reallocates a memory block.
 * @ptr: Pointer to the memory previously allocated.
 * @oldSize: Size, in bytes, of the allocated space of ptr.
 * @newSize: New size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if newSize == oldSize, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
void *_realloc(void *ptr, unsigned int oldSize, unsigned int newSize)
{
	void *nptr;

	if (ptr == NULL)
		return (malloc(newSize));

	if (newSize == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (newSize == oldSize)
		return (ptr);

	nptr = malloc(newSize);
	if (nptr == NULL)
		return (NULL);

	if (newSize < oldSize)
		_memcpy(nptr, ptr, newSize);
	else
		_memcpy(nptr, ptr, oldSize);

	free(ptr);
	return (nptr);
}

/**
 * _reallocdp - To reallocates a memory block of a double pointer.
 * @ptr: Double pointer to the memory previously allocated.
 * @oldSize: Size, in bytes, of the allocated space of ptr.
 * @newSize: New size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if newSize == oldSize, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
char **_reallocdp(char **ptr, unsigned int oldSize, unsigned int newSize)
{
	char **nptr;
	unsigned int n;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * newSize));

	if (newSize == oldSize)
		return (ptr);

	nptr = malloc(sizeof(char *) * newSize);
	if (nptr == NULL)
		return (NULL);

	for (n = 0; n < oldSize; n++)
		nptr[n] = ptr[n];

	free(ptr);

	return (nptr);
}
