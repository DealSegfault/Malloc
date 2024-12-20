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
# define MALLOC_H

# include <sys/mman.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

# define BUCKET(X) X / 16
# define DEFAULT_MMAP_THRESHOLD_MIN (128 * 1024)
# define DEFAULT_MMAP_THRESHOLD_MAX_X32 (512 * 1024)
# define DEFAULT_MMAP_THRESHOLD_MAX (4 * 1024 * 1024 * sizeof(long))
# define TINY 1
# define MEDIUM 2
# define LARGE 3
# define ERROR_SIZE 0

# define TINY_SIZE 256
# define MEDIUM_SIZE 4096

# define TINY_ZONE 28672
# define MEDIUM_ZONE 409600
# define LARGE_ZONE 1024 * 8
# define MAX_CHUNKS 1000
# define CURRENT g_store.indexes[index_iterator]
# define ENDPTR current_ptr.ptr + current_ptr.size

typedef struct			s_indexes
{
	void	*ptr;
	size_t	type;
	size_t	mmap_index;
	size_t	index_in_chunk;
	size_t	size;
	int		used;
}						t_indexes;

typedef struct			s_pagezone
{
	void	*map;
	int		used;
	int		available;
	int		total_indexes;
	int		type;
	size_t	edge;
	size_t  mapping_size;
}						t_pagezone;

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


void					free(void *ptr);
int						find_pointer_index(void *ptr);
void					increase_pagezone(t_pagezone *current, size_t n);
void					unmap(t_pagezone *current);
t_pagezone				*get_pagezone_by_type_and_index(size_t type, size_t index);
void					update_indexes_after_removal(size_t type,
	size_t removed_index, size_t nb_pagezones);
void					remove_pagezone(t_pagezone *pagezone);
void					free(void *ptr);
void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);
void					show_alloc_mem(void);
void					malloc_storage_init(void);
size_t					padding_to_16(size_t n);
size_t					malloc_type(size_t size);
void					*mmap_proxy(size_t size);
void					create_map(size_t type, size_t size);
void					create_ptr_index(void *ptr, size_t type,
	size_t mmap_index, size_t size);
void					*create_ptr(t_pagezone *current_chunk, size_t n,
	size_t type, size_t mmap_index);
void					*create_large_ptr(t_pagezone *current_chunk,
	size_t store_index, size_t n);
void					*find_store_space(size_t n);
char					*routine(int n);
void					*ft_memcpy(void *s1, const void *s2, size_t n);
void					print_address(void *ptr);
void					*reuse_ptr(int i, size_t n);
void					print_ptr(void *ptr, void *end, size_t size);
void					print_header(void *ptr, int type);
void					print_footer(int total_size);
void					ft_putstr(char *str);
void					ft_putnbr_base(int nbr, char *base);
void					ft_putchar(char c);
void					print_pagetype(size_t type, int *total_size);
int						is_free_in_map(size_t mmap_index, size_t n);
extern t_index_storage			g_store;

#endif
