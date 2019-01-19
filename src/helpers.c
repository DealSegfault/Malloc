/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 16:16:04 by mhalit            #+#    #+#             */
/*   Updated: 2019/01/19 16:16:06 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void		*ft_memcpy(void *dest, void *src, size_t n)
{
	unsigned long	*s;
	unsigned long	*d;

	d = (unsigned long *)dest;
	s = (unsigned long *)src;
	while ((unsigned int)n-- > 0)
		*d++ = *s++;
	return ((unsigned long *)dest);
}

size_t		padding_to_16(size_t n)
{
	size_t rmdr;
	size_t toadd;

	if (n < 1)
		return (0);
	rmdr = n % 16;
	if (rmdr == 0)
		return (n);
	toadd = 16 - rmdr;
	return (n + toadd);
}

size_t		malloc_type(size_t size)
{
	int		page_size;
	size_t	padded_size;

	if (size <= 0)
		return (0);
	padded_size = padding_to_16(size);
	page_size = getpagesize();
	if (padded_size < 1)
		return (0);
	if (padded_size <= TINY_SIZE)
		return (TINY);
	if (padded_size > TINY_SIZE && padded_size < page_size)
		return (MEDIUM);
	else
		return (LARGE);
	return (0);
}

void		*mmap_proxy(size_t size)
{
	void	*ptr;

	ptr = mmap(0, size,
	PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0);
	return (ptr);
}

void		*reuse_ptr(int i, size_t n)
{
	g_store.indexes[i].size = n;
	g_store.indexes[i].used = 1;
	return (g_store.indexes[i].ptr);
}
