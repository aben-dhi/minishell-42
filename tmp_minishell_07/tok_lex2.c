/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_lex2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:41:53 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/09 16:42:00 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_squote(char *str, int *i, t_token *token)
{
	t_token	*new;
	int		j;

	j = *i + 1;
	*i += 2;
	while (str[*i] && str[*i] != '\'')
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

	j = *i + 1;
	*i += 2;
	while (str[*i] && str[*i] != '\"')
		*i += 1;
	new = malloc(sizeof(t_token));
	new->value = ft_substr(str, j, *i - j);
	new->type = DQUOTE;
	new->next = NULL;
	ft_lstadd_back1(&token, new);
	*i += 1;
	return (token);
}