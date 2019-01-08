#include "../includes/malloc.h"

void        increase_pagezone(t_pagezone *current, size_t n)
{
    current->available += n;
    current->used -= n;
}

void        ft_free(void *ptr)
{
    size_t i;
    t_indexes index;
    i = 0;
    while (i <= store.total_indexes)
    {   
        // printf("%p ? %p\n", store.indexes[i].ptr, ptr);
        if (store.indexes[i].ptr == ptr)
        {
            index = store.indexes[i];
            store.indexes[i].used = 0;
            if (index.type == TINY)
                increase_pagezone(store.tiny + index.mmap_index, index.size);
            if (index.type == MEDIUM)
                increase_pagezone(store.medium + index.mmap_index, index.size);
        } 
        i++;
    }
}