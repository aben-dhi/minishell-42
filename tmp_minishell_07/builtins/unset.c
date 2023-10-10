/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:29:33 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/10 16:26:19 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_unset(t_token *token, t_env *env)
{
	t_env	*e_tmp;
	t_env	*x;
	t_token	*t_tmp;

	if (token->next == NULL)
		return (env);
	t_tmp = token->next;
	while (t_tmp)
	{
		e_tmp = env;
		while (e_tmp)
		{
			if (ft_strcmp(e_tmp->envar, t_tmp->value) == 0)
			{
				x = e_tmp;
				if (e_tmp->prev != NULL) 
					e_tmp->prev->next = e_tmp->next;
				else
					env = e_tmp->next;
				if (e_tmp->next != NULL)
					e_tmp->next->prev = e_tmp->prev;
				e_tmp = e_tmp->prev;
				// free_node(x);
				break ;
			}
			else
				e_tmp = e_tmp->next;
		}
		t_tmp = t_tmp->next;
	}
	return (env);
}

void	execute_unset(t_token *token, t_env *env)
{
	env = ft_unset(token, env);
}
