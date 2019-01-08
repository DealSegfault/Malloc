#include "../includes/malloc.h"

int		check_base(char *base)
{
	int	i;
	int	z;

	i = 0;
	z = 0;
	if (base[0] == '\0' || base[1] == '\0')
		return (0);
	while (base[i])
	{
		z = i + 1;
		if (base[i] == '+' || base[i] == '-')
			return (0);
		if (base[i] < 32 || base[i] > 126)
			return (0);
		while (base[z])
		{
			if (base[i] == base[z])
				return (0);
			z++;
		}
		i++;
	}
	return (1);
}

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

void	ft_putnbr_base(int nbr, char *base)
{
	int	size_base;
	int	nbr_final[100];
	int	i;

	i = 0;
	size_base = 0;
	if (check_base(base))
	{
		if (nbr < 0)
			nbr = -nbr;
		while (base[size_base])
			size_base++;
		while (nbr)
		{
			nbr_final[i] = nbr % size_base;
			nbr = nbr / size_base;
			i++;
		}
		while (--i >= 0)
			ft_putchar(base[nbr_final[i]]);
	}
}

void    print_address(void  *ptr)
{
    write(1, "0x", 2);
    ft_putnbr_base((unsigned long long )ptr, "ABCDEF0123456789");
}

void    show_alloc_mem(void)
{
    int tiny_map_iterator = 0;
    int large_map_iterator = 0;
    int index_iterator = 0;
	int total_size = 0;
    t_indexes current_ptr;

	printf("TINY : %p\n", (void *)store.tiny);
    while (index_iterator <= store.total_indexes)
    {
        current_ptr = store.indexes[index_iterator];
        // print_address(current_ptr.ptr);
		if (current_ptr.type == TINY && store.indexes[index_iterator].used)
		{
			printf("%p - %p : %zu octets\n", current_ptr.ptr, current_ptr.ptr + current_ptr.size, current_ptr.size);	
        	total_size += current_ptr.size;
		}	
		// printf("Type: %zu Mmap_index %zu Position %zu, Address %p\n", current_ptr.type, current_ptr.mmap_index, current_ptr.index_in_chunk, (void *)current_ptr.ptr);
        // printf("%d\n", index_iterator++);
        index_iterator++;
    }
	index_iterator = 0;
	printf("SMALL : %p\n", (void *)store.medium);
	while (index_iterator <= store.total_indexes)
    {
		if (store.indexes[index_iterator].type == MEDIUM && store.indexes[index_iterator].used)
		{
			printf("%p - %p : %zu octets\n", store.indexes[index_iterator].ptr, store.indexes[index_iterator].ptr + store.indexes[index_iterator].size, store.indexes[index_iterator].size);
        	total_size += current_ptr.size;
		}
		index_iterator++;
    }

	index_iterator = 0;
	printf("LARGE : %p\n", (void *)store.large);
	while (++index_iterator <= store.total_indexes)
    {
		if (store.indexes[index_iterator].type >= LARGE && store.indexes[index_iterator].used)
		{
			printf("%p - %p : %zu octets\n", store.indexes[index_iterator].ptr, store.indexes[index_iterator].ptr + store.indexes[index_iterator].size, store.indexes[index_iterator].size);
        	total_size += current_ptr.size;
		}
        index_iterator++;
    }
	printf("Total : %d octets\n", total_size);
}