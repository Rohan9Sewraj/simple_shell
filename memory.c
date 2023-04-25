#include "my_shell.h"

/**

my_bfree - deallocates memory pointed to by a pointer and sets it to NULL
@ptr: address of the pointer to deallocate
Return: 1 if memory is deallocated, 0 otherwise.
*/
int my_bfree(void **ptr)
{
if (ptr && *ptr)
{
free(*ptr);
*ptr = NULL;
return (1);
}
return (0);
}