/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 16:07:40 by mhalit            #+#    #+#             */
/*   Updated: 2019/01/19 16:07:42 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void		*realloc(void *ptr, size_t size)
{
	void		*newptr;
	size_t		index_iterator;

	index_iterator = -1;
	newptr = NULL;
	if (g_store.total_indexes == 0)
		return (malloc(size));
	while (++index_iterator <= g_store.total_indexes)
	{
		if (CURRENT.ptr == ptr)
		{
			if (CURRENT.size >= size && CURRENT.type != LARGE)
				return (newptr);
			else
			{	
				free(ptr);
				if (!(newptr = malloc(size)))
					return (NULL);
				newptr = ft_memcpy(newptr, CURRENT.ptr, CURRENT.size);
				return (newptr);
			}
		}
	}
	return (newptr);
}
