NAME=	minishell

SRCS=	srcs/main.c	\
		srcs/ft/ft_strlen.c		\
		srcs/ft/ft_strcpy.c		\
		srcs/ft/ft_strncpy.c	\
		srcs/ft/ft_strcat.c		\
		srcs/ft/ft_strncat.c	\
		srcs/ft/ft_strncmp.c	\
		srcs/ft/ft_putstr_fd.c	\
		srcs/ft/ft_putchar_fd.c	\
		srcs/ft/ft_strndup.c	\
		srcs/ft/ft_strchr.c		\
		srcs/display/prompt.c	\
		srcs/parsing/get_next_line.c	\
		srcs/parsing/utils.c			\
		srcs/parsing/error.c			\
		srcs/parsing/parse_line.c		\
		srcs/parsing/check_line.c		\
		srcs/parsing/parse_command.c	\
		srcs/parsing/check_command.c	\
		srcs/parsing/parse_path.c		\
		srcs/built_in/echo.c	\
		srcs/built_in/cd.c
OBJS=	$(SRCS:.c=.o)

CC=		clang
CFLAGS=	-Wall -Wextra -Werror -I./includes/ -g3 -fsanitize=address

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
