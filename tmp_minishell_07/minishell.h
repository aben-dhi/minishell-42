/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:49:40 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/15 03:46:47 by aben-dhi         ###   ########.fr       */
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
# define REDIR_IN "redir_in"
# define REDIR_OUT "redir_out"
# define REDIR_APPEND "redir_append"
# define HEREDOC "heredoc"
# define PIPE "pipe"
# define VAR "var"
# define ARG "arg"
# define SQUOTE "squote"
# define DQUOTE "dquote"
# define LPAREN "lparen"
# define RPAREN "rparen"
# define OPT	"opt"
# define SEMICOLON "semicolon"
# define FILE "file"
# define REDIR_ERR "redir_err"

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
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_ghk
{
	t_token	*token;
	t_env	*env;
	int		exit_status;
}	t_ghk;

//libft_utils:
void	ft_lstadd_back1(t_token **lst, t_token *new);
void	ft_lstadd_back2(t_env **lst, t_env *new);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_isalnum(int c);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *src);
char	**ft_split(char const *s, char c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strcmp1(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s1);
char	*ft_strtrim(char *s1, char *set);
void	ft_putstr_fd(char *s, int fd);
char 	*ft_strjoin_realloc(char *s1, const char *s2, size_t *s1_len);
char    *ft_realloc(char *str, int size);
char	*ft_strlcpy(char *dest, char *src, int size);

//parser:
// void	ft_assign_type(t_token **token);
int		ft_check_syntax(char *line);
t_token	*ft_str(char *str, int *i, t_token *token);
t_token	*ft_cmd(char *str, int *i, t_token *token);
int		ft_parse(char *line, t_env *env);
char	*expand(char *str, t_env *env, t_token *token);
int		check_args(t_token *token);
void	redir_type(t_token *token);
void	expand_dq(t_token *token, t_env *env);
// t_token	*ft_lstlast(t_token *lst);
t_token	*ft_redir(char *str, int *i, t_token *token);
t_token	*ft_pipe(char *str, int *i, t_token *token);
t_token	*ft_var(char *str, int *i, t_token *token, t_env *env);
t_token	*ft_squote(char *str, int *i, t_token *token);
t_token	*ft_dquote(char *str, int *i, t_token *token);
t_token	*ft_semicolon(char *str, int *i, t_token *token);
void	ft_redir_out(char *outfile, char *reded_str);
void	ft_redir_append(char *outfile, char *reded_str);

//utils:
void	free_arr(char **array);
void	free_node(t_env *env);
char	*lower_pwd(char *str);
char	*lower_env(char *str);
char	*lower_echo(char *str);
int		find_in_list(t_token *token, char *to_find);

//builtins:
t_env	*ft_env_fill(char **envp);
void	execute_env(t_env *env);
void	execute_export(t_token *token, t_env *env);
void	execute_unset(t_token *token, t_env *env);
void	execute_pwd(t_token *token, t_env *env);
void	execute_cd(t_token *token, t_env *env);
void	execute_echo(t_token *token);
void	execute_builtins(t_token *token, t_env *env);

#endif