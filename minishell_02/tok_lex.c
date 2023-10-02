/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_lex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 23:30:43 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/01 15:48:29 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_redir(char *str, int *i, t_token *token)
{
	t_token	*new;
	int		j;

	j = *i;
	if (str[*i] == '>' && str[*i + 1] == '>')
		*i += 2;
	else if (str[*i] == '<' && str[*i + 1] == '<')
		*i += 2;
	else
		*i += 1;
	new = malloc(sizeof(t_token));
	new->value = ft_substr(str, j, *i - j);
	new->type = REDIR;
	new->next = NULL;
	ft_lstadd_back1(&token, new);
	return (token);
}

t_token	*ft_pipe(char *str, int *i, t_token *token)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->value = ft_substr(str, *i, 1);
	new->type = PIPE;
	new->next = NULL;
	ft_lstadd_back1(&token, new);
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

t_token	*ft_var(char *str, int *i, t_token *token, t_env *env)
{
	t_token	*new;
	int		j;

	j = *i;
	*i += 1;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_' || str[*i] == '{' || str[*i] == '}'))
		*i += 1;
	new = malloc(sizeof(t_token));
	new->value = ft_substr(str, j, *i - j);
	new->value = expand(new->value, env, new);
	new->type = VAR;
	new->next = NULL;
	ft_lstadd_back1(&token, new);
	return (token);
}

t_token	*ft_str(char *str, int *i, t_token *token)
{
	t_token	*new;
	int		j;

	j = *i;
	while (str[*i] && !ft_strchr("><|; ", str[*i]))
		*i += 1;
	new = malloc(sizeof(t_token));
	new->value = ft_substr(str, j, *i - j);
	new->type = ARG;
	new->next = NULL;
	ft_lstadd_back1(&token, new);
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
	ft_lstadd_back1(&token, new);
	*i += 1;
	return (token);
}

t_token	*ft_cmd(char *str, int *i, t_token *token)
{
	t_token	*new;
	int		j;

	j = *i;
	while (str[*i] && !ft_strchr("><|; ", str[*i]))
		*i += 1;
	new = malloc(sizeof(t_token));
	new->value = ft_substr(str, j, *i - j);
	new->type = CMD;
	new->next = NULL;
	ft_lstadd_back1(&token, new);
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
	ft_lstadd_back1(&token, new);
	*i += 1;
	return (token);
}