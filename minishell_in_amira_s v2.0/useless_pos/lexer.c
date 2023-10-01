/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 23:25:18 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/09/30 23:29:45 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//We are gonna assign each value it tag or type

// void	ft_assign_type(t_token **token)
// {
// 	t_token	*current;

// 	current = *token;
// 	if (*token && ((*token)->value[0] != '<' && (*token)->value[0] != '>'))
// 	{
// 		(*token)->type = CMD;
// 		*token = (*token)->next;
// 		while (*token)
// 		{
// 			if (ft_strcmp((*token)->prev->type, "cmd") == 0
// 				&& (*token)->value[0] == '-')
// 				(*token)->type = OPT;
// 			else if (ft_strcmp((*token)->prev->type, "cmd") == 0
// 				&& (*token)->value[0] == '$')
// 				(*token)->type = VAR;
// 			else if (ft_strcmp((*token)->prev->type, "cmd") != 0
// 				&& (*token)->value[0] == '|')
// 				(*token)->type = PIPE;
// 			else
// 				(*token)->type = ARG;
// 			(*token) = (*token)->next;
// 		}
// 	}
// 	*token = current;
// }
