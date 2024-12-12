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

void	*create_large_ptr(t_pagezone *current_chunk, size_t store_index, size_t n)
{
    void    *ptr;

    ptr = current_chunk->map;
    current_chunk->used = padding_to_16(n);
    current_chunk->total_indexes = 1;
    current_chunk->available = 0;
    current_chunk->type = LARGE;
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
	g_store.indexes[g_store.total_indexes] = local_store;
	g_store.total_indexes++;
}

void *create_ptr(t_pagezone *current_chunk, size_t n, size_t type, size_t mmap_index)
{
    void *ptr;
    size_t n_padded;
	
	n_padded = padding_to_16(n);
    current_chunk->edge = (current_chunk->edge + 15) & ~((size_t)15);

    ptr = current_chunk->map + current_chunk->edge;
    current_chunk->edge += n_padded;
    current_chunk->used += n_padded;
    current_chunk->available -= n_padded;
    current_chunk->total_indexes++;

    create_ptr_index(ptr, type, mmap_index, n);
    return ptr;
}


void select_map(size_t type, t_pagezone **store_type, size_t *tail, size_t *size_zone, size_t size)
{
    size_t pagesize;

	pagesize = getpagesize();
    if (type == TINY)
    {
        *store_type = g_store.tiny;
        *tail = g_store.nb_tiny++;
        *size_zone = ((TINY_SIZE * 100 + pagesize - 1) / pagesize) * pagesize;
    }
    else if (type == MEDIUM)
    {
        *store_type = g_store.medium;
        *tail = g_store.nb_medium++;
        *size_zone = ((MEDIUM_SIZE * 100 + pagesize - 1) / pagesize) * pagesize;
    }
    else if (type == LARGE)
    {
        *store_type = g_store.large;
        *tail = g_store.nb_large++;
        *size_zone = ((size + pagesize - 1) / pagesize) * pagesize;
    }
}


void create_map(size_t type, size_t size)
{
    t_pagezone  *store_type;
    size_t      tail;
    size_t      size_zone;

    select_map(type, &store_type, &tail, &size_zone, size);
    store_type[tail].map = mmap_proxy(size_zone);
    store_type[tail].used = 0;
    store_type[tail].available = size_zone;
    store_type[tail].total_indexes = 0;
    store_type[tail].edge = 0;
    store_type[tail].type = type;
	store_type[tail].mapping_size = size_zone;
}

