#include "../includes/malloc.h"

void        double_free_error(void *ptr) {
    ft_putstr("a.out(PID, Address) malloc: *** error for object %p: pointer being freed was not allocated\n\
*** set a breakpoint in malloc_error_break to debug\n\
[1]    7982 abort      ./a.out");
    print_address(ptr);
}

void        increase_pagezone(t_pagezone *current, size_t n)
{
    current->available += n;
    current->used -= n;
}

void        free(void *ptr)
{
    size_t i;
    t_indexes index;
    i = 0;

    if (ptr == NULL)
        return ;
    while (i <= g_store.total_indexes)
    {   
        // printf("%p ? %p\n", g_store.indexes[i].ptr, ptr);
        if (g_store.indexes[i].ptr == ptr)
        {
            index = g_store.indexes[i];
            if (g_store.indexes[i].used == 0)
                return double_free_error(ptr);
            g_store.indexes[i].used = 0;
            if (index.type == TINY)
                increase_pagezone(g_store.tiny + index.mmap_index, index.size);
            if (index.type == MEDIUM)
                increase_pagezone(g_store.medium + index.mmap_index, index.size);
        } 
        i++;
    }
}