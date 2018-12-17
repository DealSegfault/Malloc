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

int main(int argc, char **argv)
{
	char *str;
	int nb;
	int i = -1;
	nb = atoi(argv[1]);
	str = (char *)mmap(0, nb + 1,
			PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	while (++i < nb)
		str[i] = 'X';
	str[i] = '\0';
	printf("%s\n", str);
	return 0;
}
