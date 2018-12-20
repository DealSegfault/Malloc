/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:51:02 by mhalit            #+#    #+#             */
/*   Updated: 2018/12/17 17:08:54 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int first_use = 0;
int mem_space_available = 0;
int mem_space_allocated = 0;
t_index_storage store;

size_t	padding_to_16(size_t n)
{
	size_t rmdr;
	size_t toadd;

	if (n < 1)
		return(0);
	rmdr = n % 16;
	if (rmdr == 0)
		return n;
	toadd = 16 - rmdr;
	return (n + toadd);
}

size_t	malloc_type(size_t size)
{
	int nbr_block;
	int page_size;
	size_t padded_size;

	padded_size = padding_to_16(size);
	nbr_block = 0;
	page_size = getpagesize();
	if (padded_size < 1)
		return (ERROR_SIZE);
	if (padded_size <= TINY_SIZE)
		return (TINY);
	if (padded_size > TINY_SIZE &&  padded_size < MEDIUM_SIZE)
		return (MEDIUM);
	else
		return (LARGE);
	return (0);
}

void	*mmap_proxy(size_t size)
{
	void	*ptr;

	ptr = mmap(0, size,
	PROT_READ | PROT_WRITE,
	MAP_ANON | MAP_PRIVATE, -1, 0);
	return (ptr);
}

void	create_map(size_t type)
{
	t_pagezone *store_type;
	size_t	tail;
	size_t	size_zone;

	if (type == 0)
		return ;
	if (type == TINY)
	{
		store_type = store.tiny;
		tail = store.nb_tiny;
		size_zone = TINY_SIZE;
		store.nb_tiny = store.nb_tiny + 1;
	}
	if (type == MEDIUM)
	{
		store_type = store.medium;
		tail = store.nb_medium;
		size_zone = MEDIUM_SIZE;
		store.nb_medium = store.nb_medium + 1;
	}
	if (type >= LARGE)
	{
		store_type = store.large;
		tail = store.nb_large;
		size_zone = type;
		store.nb_large = store.nb_large + 1;
	}
	if (tail != 0)
		tail++;
	store_type[tail].map = mmap_proxy(size_zone);
	store_type[tail].used = 0;
	store_type[tail].available = size_zone;
	store_type[tail].total_indexes = 0;
	return ;
}

void malloc_storage_init(void)
{
	size_t malloc_internal_size;

	// store = (t_index_storage)mmap_proxy(sizeof(t_index_storage));
	if (store.is_init == 1)
		return ;
	store.is_init = 1;
	store.tiny = mmap_proxy(TINY_ZONE);
	store.medium = mmap_proxy(MEDIUM_ZONE);
	store.large = mmap_proxy(LARGE_ZONE);
	store.indexes = mmap_proxy(TINY_ZONE + MEDIUM_ZONE + LARGE_ZONE);
	store.nb_tiny = 0;
	store.nb_medium = 0;
	store.nb_large = 0;

}
// void	find_chunk_space(size_t n, void )

int		find_available_chunk(t_pagezone *current_type, size_t n, int nb_pagezone, int *i)
{
	int j;

	j = *i;
	while (j < nb_pagezone)
	{
		if (current_type[j].available >= n)
		{
			*i = j;
			return (1);
		}
		j = j + 1;
	}	
	return (0);
}

size_t	find_store_space(size_t n)
{
	size_t	type;
	size_t	available_chunk;
	size_t	nb_chunk;
	int		chunk_index;
	t_pagezone *page_type;

	chunk_index = 0;
	type = malloc_type(n);
	if (type == TINY)
	{
		page_type = store.tiny;
		nb_chunk = store.nb_tiny;
	}
	if (find_available_chunk(page_type, n, nb_chunk, &chunk_index))
	{
		// if (find_chunk_space(page_type, n, chunk_index)
	}
	else // create new pagezone for type
	{
		create_map(type);
		find_store_space(n);
	}

	return (0);
}

void	*ft_malloc(size_t n)
{
	if (n < 1)
		return (NULL);
	malloc_storage_init();
	find_store_space(n);
	return (NULL);
}

int main(int argc, char **argv)
{
	char *str1;
	char *str2;
	char *str3;
	char *str4;
	char *str5;
	char *str6;
	char *str7;

	// str1 = ft_malloc(-1);
	// str2 = ft_malloc(0);
	// str3 = ft_malloc(1);	
	// str4 = ft_malloc(10);
	str5 = ft_malloc(100);
	// str6 = ft_malloc(1000);
	// str7 = ft_malloc(1000);

	// nb = atoi(argv[1]);
	// str = ft_malloc(nb + 1);
	// while (++i < nb)
	// 	str[i] = 'X';
	// str[i] = '\0';

	return 0;
}
