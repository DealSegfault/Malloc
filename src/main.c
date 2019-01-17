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
	char c = 'X';
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

char *routine_realloc(char *src, int n)
{
	char *str;
	int i = 0;
	char c = 'X';
	if (!(str = ft_realloc(src, n + 1)))
		return (NULL);
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	str[i] = '\0';
	return str;
}


int main()//int argc, char **argv
{
	char *str;
	// char *str1;
	int i = 0;
	
	while (i < 100)
	{
		str = routine(i);
		i++;
	}
	i = 0;

	// while(i < 400)
	// {
	// 	str = routine_realloc(str, i);
	// 	// printf("i = %d\nNew Ptr: %p\n\n", i, str);
	// 	i++;
	// }
	// show_alloc_mem();

    // // str = routine(10, 'X');
    // // ft_free(str);
    // // str1 = routine(10, 'a');
    // printf("Old %p Content: %s\n New %p Content %s\n ", str, str, str1, str1);
    // // // show_alloc_mem();
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
	return 0;
}