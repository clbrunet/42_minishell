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
		srcs/ft/ft_strchr.c		\
		srcs/ft/ft_strcmp.c		\
		srcs/ft/ft_lstsize.c	\
		srcs/ft/ft_strdup.c		\
		srcs/ft/ft_isalpha.c	\
		srcs/ft/ft_isdigit.c	\
		srcs/ft/ft_isalnum.c	\
		srcs/display/prompt.c	\
		srcs/parsing/get_next_line.c\
		srcs/parsing/utils.c		\
		srcs/parsing/free.c			\
		srcs/parsing/parse_line.c	\
		srcs/parsing/check_line.c	\
		srcs/parsing/parse_cmd.c	\
		srcs/built_in/echo.c	\
		srcs/built_in/cd.c		\
		srcs/built_in/export.c	\
		srcs/built_in/env.c		\
		srcs/execution/execute_cmds.c		\
		srcs/execution/execute_cmds2.c		\
		srcs/execution/execute_cmds_utils.c	\
		srcs/execution/redirect_stdin.c		\
		srcs/execution/dup_io.c				\
		srcs/execution/search_built_in.c	\
		srcs/execution/search_cmd.c

OBJS=	$(SRCS:.c=.o)

CC=		clang
CFLAGS=	-Wall -Wextra -Werror -I./includes/ -g3 -fsanitize=address
# CFLAGS=	-Wall -Wextra -Werror -I./includes/ -g3

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
