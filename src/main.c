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

char *routine(int n, char c)
{
	char *str;
	int i = 0;

	if (!(str = ft_malloc(n + 1)))
		return (NULL);
	while (i < n)
	{
		str[i] = c;
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
    
    str = routine(10, 'X');
    ft_free(str);
    str1 = routine(10, 'a');
    printf("Old %p Content: %s\n New %p Content %s\n ", str, str, str1, str1);
    // show_alloc_mem();

    // routine(10);	
    // show_alloc_mem();
    // ft_free(str);
    // while (i < 10)
	// {
	// 	str = routine(i);
	// 	i += 1;
	// }
	// i = 0;
	// while (i < 10)
	// {
	// 	str = routine(i * 100);
	// 	i++;
	// }
	// i = 0;
	// while (i < 10)
	// {
	// 	str = routine(3000 + i);
	// 	i++;
	// }
	// show_alloc_mem();
	return 0;
}