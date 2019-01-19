#include "../includes/malloc.h"

void        double_free_error(void *ptr) {
    printf("a.out(PID, Address) malloc: *** error for object %p: pointer being freed was not allocated\n\
*** set a breakpoint in malloc_error_break to debug\n\
[1]    7982 abort      ./a.out", ptr);
}

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

    if (ptr == NULL)
        return ;
    while (i <= store.total_indexes)
    {   
        // printf("%p ? %p\n", store.indexes[i].ptr, ptr);
        if (store.indexes[i].ptr == ptr)
        {
            index = store.indexes[i];
            if (store.indexes[i].used == 0)
                return double_free_error(ptr);
            store.indexes[i].used = 0;
            if (index.type == TINY)
                increase_pagezone(store.tiny + index.mmap_index, index.size);
            if (index.type == MEDIUM)
                increase_pagezone(store.medium + index.mmap_index, index.size);
        } 
        i++;
    }
}