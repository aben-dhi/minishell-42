NAME	= minishell

SRCS	= minishell.c parsing.c syntax.c utils.c check_args.c redir_type.c redir_fcts.c tok_lex2.c libft_utils/ft_realloc.c \
			builtins/echo.c builtins/pwd.c builtins/cd.c builtins/env.c builtins/export.c builtins/unset.c builtins/exec_builtins.c\
			libft_utils/ft_substr.c libft_utils/ft_lstadd_back.c libft_utils/ft_isalnum.c libft_utils/ft_strchr.c \
			libft_utils/ft_strlen.c libft_utils/ft_lstlast.c libft_utils/ft_split.c libft_utils/ft_strcpy.c libft_utils/ft_strcmp.c \
			tok_lex.c expand.c libft_utils/ft_strjoin.c libft_utils/ft_strdup.c libft_utils/ft_putstr_fd.c libft_utils/ft_strtrim.c \
			
OBJS	= $(SRCS:.c=.o)

CC		= CC

FLAGS	= -Wall -Wextra -Werror

READLINE = $(shell brew --prefix readline)

RDFLAGS = -L $(READLINE)/lib -I $(READLINE)/include

all: $(NAME)

%.o: %.c
		$(CC) $(FLAGS) -c $< -o $@
$(NAME): $(OBJS)
		$(CC) $(OBJS) -lreadline $(RDFLAGS) -o $(NAME)
clean:
		rm -f $(OBJS)
fclean: clean
		rm -f $(NAME)
re: fclean all

.PHONY	= all clean fclean re