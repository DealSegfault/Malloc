/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 17:30:11 by mhalit            #+#    #+#             */
/*   Updated: 2019/01/19 17:30:12 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void		double_free_error(void *ptr)
{
	ft_putstr("Double free at : ");
	print_address(ptr);
	return ;
}

void		increase_pagezone(t_pagezone *current, size_t n)
{
	current->available += n;
	current->used -= n;
}

void		free(void *ptr)
{
	size_t		i;
	t_indexes	index;

	i = -1;
	if (ptr == NULL)
		return ;
	while (++i <= g_store.total_indexes)
	{
		if (g_store.indexes[i].ptr == ptr)
		{
			index = g_store.indexes[i];
			if (g_store.indexes[i].used == 0)
				return (double_free_error(ptr));
			g_store.indexes[i].used = 0;
			if (index.type == TINY)
				increase_pagezone(g_store.tiny + index.mmap_index, index.size);
			if (index.type == MEDIUM)
				increase_pagezone(g_store.medium + index.mmap_index,
				index.size);
		}
	}
}
