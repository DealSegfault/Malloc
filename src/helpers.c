#include "../includes/malloc.h"

size_t	padding_to_16(size_t n)
{
	size_t rmdr;
	size_t toadd;

	if (n < 1)
		return(0);
	rmdr = n % 16;
	if (rmdr == 0)
		return n;
	toadd = 16 - rmdr;
	return (n + toadd);
}

size_t	malloc_type(size_t size)
{
	int page_size;
	size_t padded_size;

	if (size <= 0)
		return (0);
	padded_size = padding_to_16(size);
	page_size = getpagesize();
	if (padded_size < 1)
		return (0);
	if (padded_size <= TINY_SIZE)
		return (TINY);
	if (padded_size > TINY_SIZE &&  padded_size < MEDIUM_SIZE)
		return (MEDIUM);
	else
		return (LARGE);
	return (0);
}

void	*mmap_proxy(size_t size)
{
	void	*ptr;

	ptr = mmap(0, size,
	PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0);
	return (ptr);
}
