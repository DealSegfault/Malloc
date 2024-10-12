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

void		*ft_memcpy(void *s1, const void *s2, size_t n)
{
	char	*c1;
	char	*c2;

	if (n == 0 || s1 == s2)
		return (s1);
	c1 = (char *)s1;
	c2 = (char *)s2;
	while (--n)
		*c1++ = *c2++;
	*c1 = *c2;
	return (s1);
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

size_t malloc_type(size_t size)
{
    size_t padded_size = padding_to_16(size);

    if (padded_size <= TINY_SIZE)
        return TINY;
    else if (padded_size <= MEDIUM_SIZE)
        return MEDIUM;
    else
        return LARGE;
}

void *mmap_proxy(size_t size)
{
    void *ptr;

    ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (ptr == MAP_FAILED)
        return NULL;
    return ptr;
}


void		*reuse_ptr(int i, size_t n)
{
	g_store.indexes[i].size = n;
	g_store.indexes[i].used = 1;
	return (g_store.indexes[i].ptr);
}
