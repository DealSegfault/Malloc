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

void		create_map(size_t type)
{
	t_pagezone *store_type;
	size_t	tail;
	size_t	size_zone;

	if (type == 0)
		return ;
	if (type == TINY)
	{
		store_type = g_store.tiny;
		tail = g_store.nb_tiny;
		size_zone = TINY_SIZE * 100;
		g_store.nb_tiny = g_store.nb_tiny + 1;
	}
	if (type == MEDIUM)
	{
		store_type = g_store.medium;
		tail = g_store.nb_medium;
		size_zone = MEDIUM_SIZE * 100;
		g_store.nb_medium = g_store.nb_medium + 1;
	}
	if (type >= LARGE)
	{
		store_type = g_store.large;
		tail = g_store.nb_large;
		size_zone = type;
		g_store.nb_large = g_store.nb_large + 1;
	}
	if (tail != 0)
		tail++;
	store_type[tail].map = mmap_proxy(size_zone);
	store_type[tail].used = 0;
	store_type[tail].available = size_zone;
	store_type[tail].total_indexes = 0;
	store_type[tail].edge = 0;
	return ;
}

void		malloc_storage_init(void)
{
	if (g_store.is_init == 1)
		return ;
	g_store.is_init = 1;
	g_store.tiny = mmap_proxy(TINY_ZONE);
	g_store.medium = mmap_proxy(MEDIUM_ZONE);
	g_store.large = mmap_proxy(LARGE_ZONE);
	g_store.indexes = mmap_proxy(sizeof(t_indexes) *
		(TINY_ZONE + MEDIUM_ZONE + LARGE_ZONE) * 100);
	g_store.total_indexes = 0;
	g_store.nb_tiny = 0;
	g_store.nb_medium = 0;
	g_store.nb_large = 0;
	create_map(TINY);
	create_map(MEDIUM);
}

int		find_available_chunk(t_pagezone *current_type, size_t n,
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

void		*create_large_ptr(t_pagezone *current_chunk,
	size_t store_index, size_t n)
{
	void	*ptr;

	ptr = current_chunk->map;
	current_chunk->used = padding_to_16(n);
	current_chunk->total_indexes += 1;
	current_chunk->available = 0;
	create_ptr_index(ptr, LARGE, store_index, n);

	return (ptr);
}

void		create_ptr_index(void *ptr, size_t type,
	size_t mmap_index, size_t size)
{
	t_indexes	local_store;

	local_store.type = type;
	local_store.mmap_index = mmap_index;
	local_store.ptr = ptr;
	local_store.size = size;
	local_store.used = 1;
	g_store.total_indexes += 1;
	g_store.indexes[g_store.total_indexes] = local_store;
}

void		*create_ptr(t_pagezone *current_chunk, size_t n,
	size_t type, size_t mmap_index)
{
	void	*ptr;
	size_t	n_padded;

	n_padded = padding_to_16(n);
	ptr = current_chunk->map + current_chunk->edge;
	current_chunk->edge += n_padded;
	current_chunk->used = current_chunk->used + n_padded;
	current_chunk->total_indexes += 1;
	current_chunk->available -= n_padded;
	create_ptr_index(ptr, type, mmap_index, n);
	return (ptr);
}

void		*reuse_ptr(int i, size_t n)
{
	g_store.indexes[i].size = n;
	g_store.indexes[i].used = 1;
	return (g_store.indexes[i].ptr);
}

void		*check_current(t_pagezone **page_type, size_t *n,
	size_t *nb_chunk)
{
	int			space_found;
	size_t		type;
	int			chunk_index;

	chunk_index = 0;
	type = malloc_type(*n);
	space_found = find_available_chunk(*page_type, *n, *nb_chunk, &chunk_index);
	if (space_found == 0)
		return (create_ptr(*page_type + chunk_index, *n, type, chunk_index));
	if (space_found >= 1)
		return (reuse_ptr(space_found, *n));
	else
	{
		create_map(type);
		return (find_store_space(*n));
	}
	return (NULL);
}

void	*find_store_space(size_t n)
{
	t_pagezone	*page_type;
	size_t		type;
	size_t		nb_chunk;

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
		create_map(n);
		return (create_large_ptr(g_store.large + g_store.nb_large,
			g_store.nb_large, n));
	}
	return (check_current(&page_type, &n, &nb_chunk));
}

void	*malloc(size_t size)
{
	size_t	n;

	if (size < 1)
		return (NULL);
	n = padding_to_16(size);
	malloc_storage_init();
	return (find_store_space(n));
}
