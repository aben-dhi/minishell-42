NAME	= minishell

SRCS	= minishell.c parsing.c tokenization_stuff.c libft_utils/ft_substr.c libft_utils/ft_lstadd_back.c libft_utils/ft_isalnum.c libft_utils/ft_strchr.c libft_utils/ft_strlen.c \
			libft_utils/ft_lstlast.c

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