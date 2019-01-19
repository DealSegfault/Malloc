/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 15:35:11 by mhalit            #+#    #+#             */
/*   Updated: 2019/01/19 15:35:13 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void		show_alloc_mem(void)
{
	int total_size;

	total_size = 0;
	print_header((void *)g_store.tiny, TINY);
	print_pagetype(TINY, &total_size);
	print_header((void *)g_store.medium, MEDIUM);
	print_pagetype(MEDIUM, &total_size);
	print_header((void *)g_store.large, LARGE);
	print_pagetype(LARGE, &total_size);
	print_footer(total_size);
}

void		print_pagetype(size_t type, int *total_size)
{
	size_t			index_iterator;
	t_indexes		current_ptr;

	index_iterator = -1;
	while (++index_iterator <= g_store.total_indexes)
	{
		current_ptr = CURRENT;
		if (type >= LARGE)
		{
			if (CURRENT.type >= type && CURRENT.used == 1)
			{
				print_ptr(current_ptr.ptr, ENDPTR, current_ptr.size);
				*total_size += current_ptr.size;
			}
		}
		else
		{
			if (CURRENT.type == type && CURRENT.used == 1)
			{
				print_ptr(current_ptr.ptr, ENDPTR, current_ptr.size);
				*total_size += current_ptr.size;
			}
		}
	}
}
