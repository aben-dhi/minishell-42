/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:49:40 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/09/27 22:21:29 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define CMD 0
# define REDIR 1
# define PIPE 2
// # define SEMICOLON 3
# define VAR 3
# define STR 4
# define SQUOTE 5
# define DQUOTE 6

# define BRED "\e[1;31m"
# define RED "\033[0;31m"
# define YELLOW "\033[1;33m"
# define CX "\033[0m"
# define BLACK "\e[0;30m"
# define GREEN "\e[0;32m"
# define BGREEN "\e[1;32m"
# define BLUE "\e[0;34m"
# define PURPLE "\e[0;35m"
# define CYAN "\e[1;36m"
# define WHITE "\e[0;37m"
# define GREY "\e[1;30m"

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

//libft_utils
void	ft_lstadd_back(t_token **lst, t_token *new);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_isalnum(int c);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);

//parser
int		ft_parse(char *line);
t_token	*ft_tokenizer(char *str);
t_token	*ft_redir(char *str, int *i, t_token *token);
t_token	*ft_pipe(char *str, int *i, t_token *token);
// t_token	*ft_semicolon(char *str, int *i, t_token *token);
t_token	*ft_var(char *str, int *i, t_token *token);
t_token	*ft_str(char *str, int *i, t_token *token);
t_token	*ft_lstlast(t_token *lst);
t_token	*ft_squote(char *str, int *i, t_token *token);
t_token	*ft_dquote(char *str, int *i, t_token *token);

#endif