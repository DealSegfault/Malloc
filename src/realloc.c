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

void	*realloc(void *ptr, size_t size)
{
	int		index;
	void	*newptr;

	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	malloc_storage_init();
	index = find_pointer_index(ptr);
	if (index == -1)
		return (NULL);
	if (g_store.indexes[index].size >= size &&
		g_store.indexes[index].type != LARGE)
		return (ptr);
	newptr = malloc(size);
	if (!newptr)
		return (NULL);
	ft_memcpy(newptr, ptr, g_store.indexes[index].size);
	free(ptr);
	return (newptr);
}