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

#define DEFAULT_MMAP_THRESHOLD_MIN (128 * 1024)
#define DEFAULT_MMAP_THRESHOLD_MAX_X32 (512 * 1024)
#define DEFAULT_MMAP_THRESHOLD_MAX (4 * 1024 * 1024 * sizeof(long))
#define TINY 0
#define MEDIUM 1
#define LARGE 2
#define ERROR_SIZE -1
typedef struct			s_header
{
	size_t	size;
	void *content;
}						t_header;

// void					*ft_malloc(size_t n);

#endif
