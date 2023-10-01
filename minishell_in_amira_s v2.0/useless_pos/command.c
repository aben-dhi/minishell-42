/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 19:38:18 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/09/30 23:31:38 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this function will take a string type and (if there is no redirections at first) it will take the first word and change its type to cmd.

// t_token	*ft_cmd(char *str, int *i, t_token *token)
// {
// 	t_token	*new;
// 	int		j;

// 	j = *i;
// 	while (str[*i] && str[*i] != ' ' && str[*i] != '>' && str[*i] != '<' && str[*i] != '|')
// 		*i += 1;
// 	new = malloc(sizeof(t_token));
// 	new->value = ft_substr(str, j, *i - j);
// 	new->type = CMD;
// 	new->next = NULL;
// 	ft_lstadd_back1(&token, new);
// 	return (token);
// }