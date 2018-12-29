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

# include <sys/mman.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define BUCKET(X) X / 16
# define DEFAULT_MMAP_THRESHOLD_MIN (128 * 1024)
# define DEFAULT_MMAP_THRESHOLD_MAX_X32 (512 * 1024)
# define DEFAULT_MMAP_THRESHOLD_MAX (4 * 1024 * 1024 * sizeof(long))
# define TINY 1
# define MEDIUM 2
# define LARGE 3
# define ERROR_SIZE 0

# define TINY_SIZE 512
# define MEDIUM_SIZE 2048

# define TINY_ZONE 1024 * 32
# define MEDIUM_ZONE 1024 * 16
# define LARGE_ZONE 1024 * 8


// typedef struct			s_used_chunk
// {
// 	size_t	size_prev_chunk;
// 	size_t	size_chunk;
// 	void	*content;
// 	size_t	size_next_chunk;
// }						t_used_chunk;

// typedef struct			s_free_chunk
// {
// 	int		prev_chunk_allocated;
// 	size_t	size_chunk;
// 	void	*next_chunk;
// 	void	*prev_chunk;
// 	size_t	ununsed_space;

// 	size_t	size_next_chunk;

// }						t_free_chunk;					

typedef struct			s_indexes
{
	void	*ptr;
	size_t	type;
	size_t	mmap_index;
	size_t	index_in_chunk;
	size_t	size;
}						t_indexes;

typedef struct			s_pagezone
{
	void	*map;
	int		used;
	int		available;
	int		total_indexes;
	int		type;
	size_t	edge;
}						t_pagezone;

// typedef struct			s_medium
// {
// 	void	*map;
// 	size_t	used;
// 	size_t	available;
// 	size_t	total_indexes;
// }						t_medium;

// typedef struct			s_large
// {
// 	void	*map;
// 	size_t	used;
// 	size_t	available;
// 	size_t	total_indexes;
// }						t_large;

typedef	struct			s_index_storage
{
	t_pagezone	*tiny;
	t_pagezone	*medium;
	t_pagezone	*large;
	size_t		nb_tiny;
	size_t		nb_medium;
	size_t		nb_large;
	size_t		total_indexes;
	t_indexes	*indexes;
	int			is_init;
}						t_index_storage;

// void					*ft_malloc(size_t n);
t_index_storage store;


void    show_alloc_mem(void);
void    print_address(void  *ptr);
#endif
