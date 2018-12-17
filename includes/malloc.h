/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:52:11 by mhalit            #+#    #+#             */
/*   Updated: 2018/12/17 17:20:06 by mhalit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define RT_H

#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct			s_header
{
	size_t	size;
	void *content;
}

#endif
