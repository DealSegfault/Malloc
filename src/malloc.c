#include "../includes/malloc.h"

void	create_map(size_t type)
{
	t_pagezone *store_type;
	size_t	tail;
	size_t	size_zone;

	if (type == 0)
		return ;
	if (type == TINY)
	{
		store_type = store.tiny;
		tail = store.nb_tiny;
		size_zone = TINY_SIZE * 100;
		store.nb_tiny = store.nb_tiny + 1;
	}
	if (type == MEDIUM)
	{
		store_type = store.medium;
		tail = store.nb_medium;
		size_zone = MEDIUM_SIZE * 100;
		store.nb_medium = store.nb_medium + 1;
	}
	if (type >= LARGE)
	{
		store_type = store.large;
		tail = store.nb_large;
		size_zone = type;
		store.nb_large = store.nb_large + 1;
	}
	if (tail != 0)
		tail++;
	store_type[tail].map = mmap_proxy(size_zone);
	store_type[tail].used = 0;
	store_type[tail].available = size_zone;
	store_type[tail].total_indexes = 0;
	store_type[tail].edge = 0;
	return ;
}

void malloc_storage_init(void)
{
	// store = (t_index_storage)mmap_proxy(sizeof(t_index_storage));
	if (store.is_init == 1)
		return ;
	store.is_init = 1;
	store.tiny = mmap_proxy(TINY_ZONE);
	store.medium = mmap_proxy(MEDIUM_ZONE);
	store.large = mmap_proxy(LARGE_ZONE);
	store.indexes = mmap_proxy(sizeof(t_indexes) * (TINY_ZONE + MEDIUM_ZONE + LARGE_ZONE) * 100);
	store.total_indexes = 0;
	store.nb_tiny = 0;
	store.nb_medium = 0;
	store.nb_large = 0;
	create_map(TINY);
	create_map(MEDIUM);
}



int		is_free_in_map(size_t mmap_index, size_t n)
{
	// size_t	edge;
	size_t i;

    i = 0;
    while (i <= store.total_indexes)
    {   
        // printf("%p ? %p\n", store.indexes[i].ptr, ptr);
        if (store.indexes[i].mmap_index == mmap_index &&
			store.indexes[i].used == 0 && store.indexes[i].size >= n)
            // store.indexes[i].used = 1;
			return (i);
        i++;
    }
	return (0); // Might not free first ptr
}
int		find_available_chunk(t_pagezone *current_type, size_t n, int nb_pagezone, int *i)
{
	int j;
	int is_free;

	j = *i;
	is_free = 0;
	while (j < nb_pagezone)
	{
		if (current_type[j].available >= (int)n)
		{
			if ((is_free = is_free_in_map(j, n)))
				return (is_free);
			*i = j;
			return (0);
		}
		j = j + 1;
	}	
	return (-1);
}

void	*create_large_ptr(t_pagezone *current_chunk, size_t store_index, size_t n)
{
	void	*ptr;
	
	ptr = current_chunk->map;
	current_chunk->used = padding_to_16(n);
	current_chunk->total_indexes += 1;
	current_chunk->available = 0;
	create_ptr_index(ptr, LARGE, store_index, 0, n);

	return (ptr);
}

void	create_ptr_index(void *ptr, size_t type, size_t mmap_index, size_t edge, size_t size)
{
	t_indexes	local_store;

	local_store.type = type;
	local_store.mmap_index = mmap_index;
	local_store.index_in_chunk = edge;
	local_store.ptr = ptr;
	local_store.size = size;
	local_store.used = 1;
	store.total_indexes += 1;
	store.indexes[store.total_indexes] = local_store;
	//check free memory and swap freed memory
}

void	 *create_ptr(t_pagezone *current_chunk, size_t n, size_t type, size_t mmap_index)
{
	void	*ptr;
	size_t	n_padded;

	n_padded = padding_to_16(n);
	ptr = current_chunk->map + current_chunk->edge; //bucket 16 bytes sized
	current_chunk->edge += n_padded;
	current_chunk->used = current_chunk->used + n_padded;
	current_chunk->total_indexes += 1;
	current_chunk->available -= n_padded;
	create_ptr_index(ptr, type, mmap_index, current_chunk->edge - n_padded, n);

	return (ptr);
}

void	*reuse_ptr(int i, size_t n)
{
	store.indexes[i].size = n;
	store.indexes[i].used = 1;
	return (store.indexes[i].ptr);  
}

void	*find_store_space(size_t n)
{
	size_t	type;
	// size_t	available_chunk;
	size_t	nb_chunk;
	int		chunk_index;
	void	*ptr;
	int		space_found;

	space_found = 0;
	t_pagezone *page_type;

	chunk_index = 0;
	type = malloc_type(n);
	if (type == TINY)
	{
		page_type = store.tiny;
		nb_chunk = store.nb_tiny;
	}
	if (type == MEDIUM)
	{
		page_type = store.medium;
		nb_chunk = store.nb_medium;
	}
	if (type == LARGE)
	{
		create_map(n);
		ptr = create_large_ptr(store.large + store.nb_large, store.nb_large, n);
		return (ptr);
	}
	space_found = find_available_chunk(page_type, n, nb_chunk, &chunk_index);
	if (space_found == 0) // Create new ptr
	{
		ptr = create_ptr(page_type + chunk_index, n, type, chunk_index);
		return (ptr);
	}
	if (space_found >= 1) // Reuse old ptr from ptr indexes
		return(reuse_ptr(space_found, n));
	else // create new pagezone for type
	{
		create_map(type);
		return (find_store_space(n));
	}
	return (NULL);
}

void	*ft_malloc(size_t n)
{
	size_t	size;

	if (n < 1)
		return (NULL);
	size = padding_to_16(n);
	malloc_storage_init();
	return (find_store_space(size));
}
