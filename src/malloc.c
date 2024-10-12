/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 15:59:38 by mhalit            #+#    #+#             */
/*   Updated: 2019/01/19 15:59:39 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void		malloc_storage_init(void)
{
	if (g_store.is_init == 1)
		return ;
	g_store.is_init = 1;
	g_store.tiny = mmap_proxy(sizeof(t_pagezone) * MAX_CHUNKS);
	g_store.medium = mmap_proxy(sizeof(t_pagezone) * MAX_CHUNKS);
	g_store.large = mmap_proxy(sizeof(t_pagezone) * MAX_CHUNKS);
	g_store.indexes = mmap_proxy(sizeof(t_indexes) *
		(TINY_ZONE + MEDIUM_ZONE + LARGE_ZONE) * 100);
	g_store.total_indexes = 0;
	g_store.nb_tiny = 0;
	g_store.nb_medium = 0;
	g_store.nb_large = 0;
	create_map(TINY, 0);
	create_map(MEDIUM, 0);
}

int			find_available_chunk(t_pagezone *current_type, size_t n,
	int nb_pagezone, int *i)
{
	int j;
	int is_free;

	j = *i;
	is_free = 0;
	while (j < nb_pagezone)
	{
		if (current_type[j].available >= (int)n)
		{
			if ((is_free = is_free_in_map(j, n)))
				return (is_free);
			*i = j;
			return (0);
		}
		j = j + 1;
	}
	return (-1);
}

void		*check_current(t_pagezone *page_type, size_t n,
	size_t *nb_chunk)
{
	int			space_found;
	size_t		type;
	int			chunk_index;

	chunk_index = 0;
	type = malloc_type(n);
	space_found = find_available_chunk(page_type, n, *nb_chunk, &chunk_index);
	if (space_found == 0)
		return (create_ptr(page_type + chunk_index, n, type, chunk_index));
	if (space_found >= 1)
		return (reuse_ptr(space_found, n));
	else
	{
		create_map(type, 0);
		return (find_store_space(n));
	}
	return (NULL);
}

void		*find_store_space(size_t n)
{
	t_pagezone	*page_type;
	size_t		type;
	size_t		nb_chunk;
	void		*ptr;

	ptr = NULL;
	type = malloc_type(n);
	if (type == TINY)
	{
		page_type = g_store.tiny;
		nb_chunk = g_store.nb_tiny;
	}
	if (type == MEDIUM)
	{
		page_type = g_store.medium;
		nb_chunk = g_store.nb_medium;
	}
	if (type == LARGE)
	{
		create_map(LARGE, n);
		ptr = create_large_ptr(g_store.large + g_store.nb_large - 1,
			g_store.nb_large - 1, n);
		return (ptr);
	}
	return (check_current(page_type, n, &nb_chunk));
}

void		*malloc(size_t size)
{
	size_t	n;
	
	if (size < 1)
		return (NULL);
	n = padding_to_16(size);
	malloc_storage_init();
	return (find_store_space(n));
}
