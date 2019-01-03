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

char *routine(int n)
{
	char *str;
	int i = 0;

	if (!(str = ft_malloc(n + 1)))
		return (NULL);
	while (i < n)
	{
		str[i] = 'X';
		i++;
	}
	str[i] = '\0';
	// printf("Size: %d, address %p, type \n", n, (void *)str);
	// printf("Content : %s\n\n", str);
	return str;
}

int main(int argc, char **argv)
{
	char *str;
	char *str1;
	int i = 0;

	while (i < 10)
	{
		str = routine(i);
		i += 1;
	}
	i = 0;
	while (i < 10)
	{
		str = routine(i * 100);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		str = routine(3000 + i);
		i++;
	}
	// routine(120);
	// routine(1200);
	// routine(2000);
	// routine(3000);
	// routine(4000);


	show_alloc_mem();
	return 0;
}