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
		// write(1, str, i);
		// write(1, "\n",1);
		i++;
	}
	str[i] = '\0';
	// printf("Size: %d, address %p\n", n, (void *)str);
	// printf("Content : %s\n\n", str);
	return str;
}
int main(int argc, char **argv)
{
	char *str;
	char *str1;
	int i = 0;

	while (i < 1500)
	{
		// printf("%d ", i);
		str = routine(i);
		if ((unsigned long long)str % 16 > 0)
			exit(1);
		
		i++;
	}


	// char *str;
	// int i = 0;
	
	// str = ft_malloc(1);
	// while (i < 10)
	// {
	// 	str[i] = 'A';
	// 	i++;
	// }
	// str[i] = '\0';
	// printf("%s\n", str);
	return 0;
}
