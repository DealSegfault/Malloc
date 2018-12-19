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

# define DEFAULT_MMAP_THRESHOLD_MIN (128 * 1024)
# define DEFAULT_MMAP_THRESHOLD_MAX_X32 (512 * 1024)
# define DEFAULT_MMAP_THRESHOLD_MAX (4 * 1024 * 1024 * sizeof(long))
# define TINY 1
# define MEDIUM 2
# define LARGE 3
# define ERROR_SIZE 0

# define TINY_SIZE 512
# define MEDIUM_SIZE 1024

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

typedef struct			t_indexes
{
	void	*ptr;
	size_t	type;
	size_t	mmap_index;
	size_t	index_in_zone;
}						s_indexes;

typedef struct			t_tiny
{
	void	*tiny_mmap;
	size_t	used;
	size_t	available;
	size_t	total_indexes;
}						s_tiny;

typedef struct			t_medium
{
	void	*medium_mmap;
	size_t	used;
	size_t	available;
	size_t	total_indexes;
}						s_medium;

typedef struct			t_large
{
	void	*large_mmap;
	size_t	used;
	size_t	available;
	size_t	total_indexes;
}						s_large;

typedef	struct			s_index_storage
{
	t_tiny		*tiny;
	t_medium	*medium;
	t_large		*large;
	size_t		nb_tiny;
	size_t		nb_medium;
	size_t		nb_large;
	void		*indexes;
}						s_index_storage;

// void					*ft_malloc(size_t n);

#endif
