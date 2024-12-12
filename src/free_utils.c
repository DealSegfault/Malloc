/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 17:30:11 by mhalit            #+#    #+#             */
/*   Updated: 2019/01/19 17:30:12 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_pagezone	*get_pagezone_by_type_and_index(size_t type, size_t index)
{
	if (type == TINY)
	{
		if (index < g_store.nb_tiny)
			return (&g_store.tiny[index]);
	}
	else if (type == MEDIUM)
	{
		if (index < g_store.nb_medium)
			return (&g_store.medium[index]);
	}
	else if (type == LARGE)
	{
		if (index < g_store.nb_large)
			return (&g_store.large[index]);
	}
	return (NULL);
}

void	update_indexes_after_removal(size_t type, size_t removed_index,
		size_t nb_pagezones)
{
	size_t	i;

	i = 0;
	while (i < g_store.total_indexes)
	{
		if (g_store.indexes[i].type == type)
		{
			if (g_store.indexes[i].mmap_index == nb_pagezones - 1)
				g_store.indexes[i].mmap_index = removed_index;
			else if (g_store.indexes[i].mmap_index > removed_index)
				g_store.indexes[i].mmap_index--;
		}
		i++;
	}
}

void	remove_pagezone(t_pagezone *pagezone)
{
	size_t		index;
	size_t		*nb_pagezones;
	t_pagezone	*array;

	if (pagezone->type == TINY)
	{
		array = g_store.tiny;
		nb_pagezones = &g_store.nb_tiny;
	}
	else if (pagezone->type == MEDIUM)
	{
		array = g_store.medium;
		nb_pagezones = &g_store.nb_medium;
	}
	else if (pagezone->type == LARGE)
	{
		array = g_store.large;
		nb_pagezones = &g_store.nb_large;
	}
	else
		return ;
	index = pagezone - array;
	if (index < *nb_pagezones - 1)
	{
		array[index] = array[*nb_pagezones - 1];
		update_indexes_after_removal(pagezone->type, index, *nb_pagezones);
	}
	(*nb_pagezones)--;
}