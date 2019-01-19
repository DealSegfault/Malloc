/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 15:35:20 by mhalit            #+#    #+#             */
/*   Updated: 2019/01/19 15:35:21 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void		print_address(void *ptr)
{
	write(1, "0x", 2);
	ft_putnbr_base((unsigned long long)ptr, "ABCDEF0123456789");
}

void		print_header(void *ptr, int type)
{
	if (type == TINY)
		ft_putstr("TINY : ");
	if (type == MEDIUM)
		ft_putstr("MEDIUM : ");
	if (type == LARGE)
		ft_putstr("LARGE : ");
	print_address(ptr);
	ft_putchar('\n');
}

void		print_ptr(void *ptr, void *end, size_t size)
{
	print_address(ptr);
	ft_putstr(" - ");
	print_address(end);
	ft_putstr(" : ");
	ft_putnbr_base((unsigned long long)size, "0123456789");
	ft_putstr(" octets\n");
}

void		print_footer(int total_size)
{
	ft_putstr("Total : ");
	ft_putnbr_base(total_size, "0123456789");
	ft_putstr(" octets\n");
}
