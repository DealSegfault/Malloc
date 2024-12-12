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

void	unmap(t_pagezone *current)
{
	munmap(current->map, current->mapping_size);
	current->map = NULL;
}

void	increase_pagezone(t_pagezone *current, size_t n)
{
	current->available += n;
	current->used -= n;
	if (current->used == 0)
	{
		unmap(current);
		remove_pagezone(current);
	}
}

int	find_pointer_index(void *ptr)
{
	size_t	i;

	i = 0;
	while (i < g_store.total_indexes)
	{
		if (g_store.indexes[i].ptr == ptr)
			return ((int)i);
		i++;
	}
	return (-1);
}

void	free(void *ptr)
{
	int			index;
	t_indexes	*idx;
	t_pagezone	*pagezone;

	if (ptr == NULL)
		return ;
	index = find_pointer_index(ptr);
	if (index == -1)
		return ;
	idx = &g_store.indexes[index];
	if (idx->used == 0)
		return ;
	idx->used = 0;
	pagezone = get_pagezone_by_type_and_index(idx->type, idx->mmap_index);
	if (pagezone != NULL)
		increase_pagezone(pagezone, idx->size);
}
