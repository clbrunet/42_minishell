NAME=	minishell

SRCS=	srcs/main.c	\
		srcs/ft/ft_strlen.c	\
		srcs/ft/ft_strcpy.c	\
		srcs/ft/ft_strcat.c	\
		srcs/ft/ft_strncat.c	\
		srcs/display/prompt.c	\
		srcs/parsing/get_next_line.c
OBJS=	$(SRCS:.c=.o)

CC=		clang
CFLAGS=	-Wall -Wextra -Werror -I./includes/

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

bonus:	$(NAME)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re bonus
