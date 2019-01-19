CC	=	gcc

RM	=	rm -f

NAME	=	libft_malloc_$(HOSTTYPE).so

LINK	=	libft_malloc.so

CFLAGS	=	-Wall -Wextra -Werror -fPIC

SRC	=	src/free.c			\
		src/malloc.c 		\
		src/helpers.c		\
		src/realloc.c		\
		src/show_alloc_mem.c\

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