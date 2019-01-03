#include "../includes/malloc.h"

void        ft_free(void *ptr)
{
    size_t i;

    i = 0;
    while (i <= store.total_indexes)
    {   
        // printf("%p ? %p\n", store.indexes[i].ptr, ptr);
        if (store.indexes[i].ptr == ptr)
            store.indexes[i].used = 0;
        i++;
    }
}