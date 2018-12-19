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


void	create_map(size_t type)
{
	void	*store_type;
	size_t	tail;
	size_t	size_zone;
	if (type == 0)
		return ;
	if (type == TINY)
	{
		store_type = store.tiny;
		tail = store.tiny;
		size_zone = TINY_SIZE;
	}
	if (type == MEDIUM)
	{
		store_type = store.medium;
		tail = store.nb_medium;
		size_zone = MEDIUM_SIZE;
	}
	else
	{
		store_type = store.large;
		tail = store.nb_large;
		size_zone = type;
	}
	tail++;
	store_type[tail] = mmap(0, size_zone,
			PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	return ;
}

void	*mmap_proxy(size_t size)
{
	void	*ptr;

	ptr = mmap(0, malloc_internal_size,
	PROT_READ | PROT_WRITE,
	MAP_ANON | MAP_PRIVATE, -1, 0);
	return (ptr);
}

void malloc_storage_init(void)
{
	size_t malloc_internal_size;

	store = mmap_proxy(sizeof(t_index_storage));
	store.tiny = mmap_proxy(TINY_ZONE);
	store.medium = mmap_proxy(MEDIUM_ZONE);
	store.large = mmap_proxy(LARGE_ZONE);
	store.indexes = mmap_proxy(TINY_ZONE + MEDIUM_ZONE + LARGE_ZONE);
	store.nb_tiny = 0;
	store.nb_medium = 0;
	store.nb_large = 0;
}

void	*ft_malloc(size_t n)
{
	void *out;
	void *mmap_mem;
	int ptr_pos;
	int mem_to_allocate;

	ptr_pos = 0;
	mem_to_allocate = malloc_type(n);
	if (mem_space_allocated - mem_to_allocate <= 0)
		return (NULL);//allocate more
	if (first_use == 0)
	{
		mmap_mem = (char *)mmap(0, mem_to_allocate,
			PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
		first_use = 1;
	}
	if (mmap_mem)
		mem_space_available += mem_to_allocate; 
	if (mem_space_available < 1)
		return (NULL);
	ptr_pos = mem_space_available - (int)n;
	out = mmap_mem + ptr_pos;
	return (out);
}

int main(int argc, char **argv)
{
	char *str;
	int nb;
	int i = -1;
	// nb = atoi(argv[1]);
	// str = ft_malloc(nb + 1);
	// while (++i < nb)
	// 	str[i] = 'X';
	// str[i] = '\0';
	printf("%zu\n", malloc_type(-1));
	printf("%zu\n", malloc_type(0));
	printf("%zu\n", malloc_type(420));
	printf("%zu\n", malloc_type(850));
	printf("%zu\n", malloc_type(3000));
	printf("%zu\n", malloc_type(9000));
	printf("%zu\n", malloc_type(10000));

	return 0;
}
