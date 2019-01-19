/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 17:41:06 by mhalit            #+#    #+#             */
/*   Updated: 2019/01/19 17:41:07 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

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

void		select_map(size_t type, t_pagezone **store_type,
	size_t *tail, size_t *size_zone)
{
	if (type == 0)
		return ;
	if (type == TINY)
	{
		*store_type = g_store.tiny;
		*tail = g_store.nb_tiny;
		*size_zone = TINY_SIZE * 100;
		g_store.nb_tiny = g_store.nb_tiny + 1;
	}
	if (type == MEDIUM)
	{
		*store_type = g_store.medium;
		*tail = g_store.nb_medium;
		*size_zone = MEDIUM_SIZE * 100;
		g_store.nb_medium = g_store.nb_medium + 1;
	}
	if (type >= LARGE)
	{
		*store_type = g_store.large;
		*tail = g_store.nb_large;
		*size_zone = type;
		g_store.nb_large = g_store.nb_large + 1;
	}
}

void		create_map(size_t type)
{
	t_pagezone		*store_type;
	size_t			tail;
	size_t			size_zone;

	select_map(type, &store_type, &tail, &size_zone);
	if (tail != 0)
		tail++;
	store_type[tail].map = mmap_proxy(size_zone);
	store_type[tail].used = 0;
	store_type[tail].available = size_zone;
	store_type[tail].total_indexes = 0;
	store_type[tail].edge = 0;
	return ;
}
