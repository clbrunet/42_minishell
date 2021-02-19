NAME=	minishell

SRCS=	srcs/main.c
OBJS=	$(SRCS:.c=.o)

CC=	clang
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
