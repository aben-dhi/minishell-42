/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 21:12:10 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/09 17:29:05 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//give types to redirections 

void	redir_type(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == REDIR)
		{
			if (tmp->value[0] == '>' && tmp->value[1] == '>')
				tmp->type = REDIR_APPEND;
			else if (tmp->value[0] == '<' && tmp->value[1] == '<')
				tmp->type = HEREDOC;
			else if (tmp->value[0] == '>' && tmp->value[1] != '>')
				tmp->type = REDIR_OUT;
			else if (tmp->value[0] == '<' && tmp->value[1] != '<')
				tmp->type = REDIR_IN;
			else if (tmp->value[0] == '2' && tmp->value[1] == '>')
				tmp->type = REDIR_ERR;
		}
		tmp = tmp->next;
	}
}
