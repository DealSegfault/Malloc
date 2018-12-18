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

void *ft_malloc(size_t n)
{
	void *out;
	void *mmap_mem;
	int mem_space_available;
	int ptr_pos;

	ptr_pos = 0;
	mem_space_available = DEFAULT_MMAP_THRESHOLD_MIN;

	if (n < 1)
		return (NULL);
	if (first_use == 0)
	{
		mmap_mem = (char *)mmap(0, DEFAULT_MMAP_THRESHOLD_MIN,
			PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
		first_use = 1;
	}

	ptr_pos = mem_space_available - (int)n;
	out = mmap_mem + ptr_pos;
	return (out);
}

int main(int argc, char **argv)
{
	char *str;
	int nb;
	int i = -1;
	nb = atoi(argv[1]);
	str = ft_malloc(nb + 1);
	while (++i < nb)
		str[i] = 'X';
	str[i] = '\0';
	printf("%s\n", str);
	return 0;
}
