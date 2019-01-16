#include "../includes/malloc.h"

void    *ft_realloc(void *ptr, size_t size)
{
    void        *newptr;
    t_indexes   index;
    size_t      i;
    
    i = 0;
    newptr = NULL;
    while (i <= store.total_indexes)
    {   
        if (store.indexes[i].ptr == ptr)
        {
            index = store.indexes[i];
            if (index.size > size)//Wrng 
            {
                return (newptr);
            }
            else {
                ft_free(ptr);
                newptr = ft_malloc(size);
                newptr = ft_memcpy(newptr, index.ptr, index.size);
                printf("i = %ld %s Size %ld\n", i, "Copy ", index.size);
                // store.indexes[store.total_indexes].ptr;
                return (newptr);
            }
            
        }
        i++;
    }
    return (newptr);
}