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
                ft_memcpy()
                ft_free(ptr);
                ft_malloc(size)
            }
            
        }
        i++;
    }
    return (newptr);
}