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

int malloc_type(size_t size) 
{
	int nbr_block;
	int page_size;
	
	nbr_block = 0;
	page_size = getpagesize();
	if (size < 1)
		return (ERROR_SIZE);
	if (size <= DEFAULT_MMAP_THRESHOLD_MIN)
	{
		nbr_block = (size / page_size)
		if (nbr_block < 100)
			return (TINY);
		if (nbr_block >= 100 && nbr_block < DEFAULT_MMAP_THRESHOLD_MIN / page_size);
			return (MEDIUM);
		else
			return (LARGE);
	}
}


void *ft_malloc(size_t n)
{
	void *out;
	void *mmap_mem;
	int ptr_pos;
	int mem_to_allocate;

	ptr_pos = 0;
	mem_to_allocate = size_mem_alloc(n);
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

	printf("%d\n", DEFAULT_MMAP_THRESHOLD_MIN / 4096);
	return 0;
}
