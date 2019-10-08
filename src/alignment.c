#include "malloc.h"

size_t	align_size(size_t size)
{
	return ((size + 15) & ~15);
}

size_t	needed_size(size_t size)
{
	return (4 * sizeof(void*) + align_size(size));
}
