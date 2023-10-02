/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htouil <htouil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:49:40 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/01 22:13:52 by htouil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> //remove this
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

# define CMD "cmd"
# define REDIR "redir"
// # define REDIR_OUT "redir_out"
// # define REDIR_APPEND "redir_append"
// # define HEREDOC "heredoc"
# define PIPE "pipe"
# define VAR "var"
# define ARG "arg"
# define SQUOTE "squote"
# define DQUOTE "dquote"
# define LPAREN "lparen"
# define RPAREN "rparen"
# define OPT	"opt"

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
	char			*type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*envar;
	char			*enval;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

//libft_utils
void	ft_lstadd_back1(t_token **lst, t_token *new);
void	ft_lstadd_back2(t_env **lst, t_env *new);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_isalnum(int c);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *src);
char	**ft_split(char const *s, char c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s1);

//parser
int		ft_check_syntax(char *line);
t_token	*ft_tokenizer(char *token, t_env *env);
t_token	*ft_str(char *str, int *i, t_token *token);
t_token	*ft_cmd(char *str, int *i, t_token *token);
// void	ft_assign_type(t_token **token);
int		ft_parse(char *line, t_env *env);
t_env	*ft_env_fill(char **envp);
void	ft_env(t_env *env);
t_env	*ft_export(t_token *token, t_env *env);
void	execute_builtins(t_token *token, t_env *env);
char	*expand(char *str, t_env *env, t_token *token);

// t_token	*ft_lstlast(t_token *lst);
t_token	*ft_redir(char *str, int *i, t_token *token);
t_token	*ft_pipe(char *str, int *i, t_token *token);
t_token	*ft_var(char *str, int *i, t_token *token, t_env *env);
t_token	*ft_squote(char *str, int *i, t_token *token);
t_token	*ft_dquote(char *str, int *i, t_token *token);

//utils
void	free_arr(char **array);
void	free_node(t_env *env);

#endif