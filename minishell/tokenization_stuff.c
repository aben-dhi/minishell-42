/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_stuff.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:58:05 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/09/29 17:43:15 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//we are going to use the ft_lstadd_back function to add the tokens to the linked list.

//there is chi haja smitha 2> as in redirect to the STDOUT, I need to add it as  a condition in the ft_redir function.
t_token	*ft_redir(char *str, int *i, t_token *token)
{
	t_token	*new;
	int		j;

	j = *i;
	if (str[*i] == '>' && str[*i + 1] == '>')
		*i += 2;
	else if (str[*i] == '<' && str[*i] == '<')
		*i += 2;
	else
		*i += 1;
	new = malloc(sizeof(t_token));
	new->value = ft_substr(str, j, *i - j);
	new->type = REDIR;
	new->next = NULL;
	ft_lstadd_back(&token, new);
	return (token);
}

t_token	*ft_pipe(char *str, int *i, t_token *token)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->value = ft_substr(str, *i, 1);
	new->type = PIPE;
	new->next = NULL;
	ft_lstadd_back(&token, new);
	*i += 1;
	return (token);
}

// t_token	*ft_semicolon(char *str, int *i, t_token *token)
// {
// 	t_token	*new;

// 	new = malloc(sizeof(t_token));
// 	new->value = ft_substr(str, *i, 1);
// 	new->type = SEMICOLON;
// 	new->next = NULL;
// 	ft_lstadd_back(&token, new);
// 	*i += 1;
// 	return (token);
// }

t_token	*ft_var(char *str, int *i, t_token *token)
{
	t_token	*new;
	int		j;

	j = *i;
	*i += 1;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		*i += 1;
	new = malloc(sizeof(t_token));
	new->value = ft_substr(str, j, *i - j);
	new->type = VAR;
	new->next = NULL;
	ft_lstadd_back(&token, new);
	return (token);
}

t_token	*ft_str(char *str, int *i, t_token *token)
{
	t_token	*new;
	int		j;

	j = *i;
	while (str[*i] && !ft_strchr(" \"", str[*i]))
		*i += 1;
	new = malloc(sizeof(t_token));
	new->value = ft_substr(str, j, *i - j);
	new->type = STR;
	new->next = NULL;
	ft_lstadd_back(&token, new);
	return (token);
}

t_token	*ft_squote(char *str, int *i, t_token *token)
{
	t_token	*new;
	int		j;

	j = *i;
	*i += 1;
	while (str[*i] && str[*i] != '\'')
		*i += 1;
	*i += 1;
	new = malloc(sizeof(t_token));
	new->value = ft_substr(str, j, *i - j);
	new->type = SQUOTE;
	new->next = NULL;
	ft_lstadd_back(&token, new);
	*i += 1;
	return (token);
}
t_token	*ft_dquote(char *str, int *i, t_token *token)
{
	t_token	*new;
	int		j;

	j = *i;
	*i += 1;
	while (str[*i] && str[*i] != '\"')
		*i += 1;
	*i += 1;
	new = malloc(sizeof(t_token));
	new->value = ft_substr(str, j, *i - j);
	new->type = DQUOTE;
	new->next = NULL;
	ft_lstadd_back(&token, new);
	*i += 1;
	return (token);
}

//make sure that the double quotes and single quotes are closed and parenthese are closed.
//make sure that the redirections are correct.+
//make sure that the pipes are correct.
int ft_check_syntax(char *line)
{
	int i;
	int squote;
	int dquote;
	int parenthese;

	i = 0;
	squote = 0;
	dquote = 0;
	parenthese = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			squote = !squote;
		if (line[i] == '\"')
			dquote = !dquote;	
		if (line[i] == '(')
		{
			if (!squote && !dquote) // Check if not inside quotes
				parenthese++;
		}
		if (line[i] == ')')
		{
			if (!squote && !dquote) // Check if not inside quotes
			{
				if (parenthese == 0)
					return (1); // Unclosed parenthesis detected
				parenthese--;
			}
		}
		i++;
	}
	if (parenthese == 1 || squote == 1|| dquote == 1)
		return (1); // Unclosed parenthesis, single quote, or double quote detected
	return (0); // Syntax is correct
}

