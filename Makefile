CC	=	gcc

RM	=	rm -f

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME	=	libft_malloc_$(HOSTTYPE).so

LINK	=	libft_malloc.so

CFLAGS	=	-Wall -Wextra -Werror -fPIC

SRC	=	src/free.c			\
		src/malloc.c 		\
		src/helpers.c		\
		src/realloc.c		\
		src/show_alloc_mem.c\
		src/show_helpers.c	\
		src/base_func.c		\
		src/create_map.c

OBJ	=	$(SRC:.c=.o)

$(NAME)	:	$(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -shared -o $(NAME)
		ln -sf $(NAME) $(LINK)

all	:	$(NAME)

clean	:
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all