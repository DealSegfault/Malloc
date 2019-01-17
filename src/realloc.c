#include "../includes/malloc.h"

void    *ft_realloc(void *ptr, size_t size)
{
    void        *newptr;
    t_indexes   index;
    size_t      i;
    
    i = 0;
    newptr = NULL;
    if (store.total_indexes == 0)
    {
        newptr = ft_malloc(size);
        return (newptr);
    }
    while (i <= store.total_indexes)
    {   
        if (store.indexes[i].ptr == ptr)
        {
            index = store.indexes[i];
            if (index.size >= size && index.type != LARGE)//Wrng 
            {
                return (newptr);
            }
            else {
                ft_free(ptr);
                if (!(newptr = ft_malloc(size)))
                    return (NULL);
                if (index.size > 0 && index.type < 3)
                    newptr = ft_memcpy(newptr, index.ptr, index.size);
                // printf("i = %ld %s Size %ld\n", i, "Copy ", index.size);
                // store.indexes[store.total_indexes].ptr;
                return (newptr);
            }
            
        }
        i++;
    }
    return (newptr);
}