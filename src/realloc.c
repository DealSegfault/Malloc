#include "../includes/malloc.h"

void    *realloc(void *ptr, size_t size)
{
    void    *newptr;
    t_indexes index;
    
    i = 0;
    while (i <= store.total_indexes)
    {   
        if (store.indexes[i].ptr == ptr)
        {
            index = store.indexes[i];
            if (index.size > size);
                return (newptr);
            else
            {
                ft_free(ptr);
                newptr = ft_malloc(size);
                ft_memcpy(newptr, index.ptr, index.size);
                // store.indexes[store.total_indexes].ptr;
                return (newptr);
            }
            
        }
        i++;
    }
    return (newptr);
}