/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:26:36 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/07 19:03:12 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_export(t_token *token, t_env *env)
{
	t_env	*new;
	t_env	*e_tmp;
	t_token	*t_tmp;
	char	**arg;
	char	*val;

	if (token->next == NULL)
	{
		e_tmp = env;
		while (e_tmp)
		{
			printf("declare -x %s=\"%s\"\n", e_tmp->envar, e_tmp->enval);
			e_tmp = e_tmp->next;
		}
	}
	else
	{
		t_tmp = token->next;
		while (t_tmp)
		{
			arg = ft_split(t_tmp->value, '=');
			val = ft_strtrim(arg[1], "\"");
			e_tmp = env;
			while (e_tmp)
			{
				if (ft_strcmp(e_tmp->envar, arg[0]) == 0)
				{
					e_tmp->enval = ft_strcpy(val);
					break ;
				}
				if ((ft_strcmp(e_tmp->envar, arg[0]) != 0)
					&& e_tmp->next == NULL)
				{
					new = malloc(sizeof(t_env));//might need to free this later along with the rest of the new variables.
					new->envar = ft_strcpy(arg[0]);
					new->enval = ft_strcpy(val);
					new->next = NULL;
					ft_lstadd_back2(&e_tmp, new);
					break ;
				}
				e_tmp = e_tmp->next;
			}
			free (val);
			free_arr(arg);
			t_tmp = t_tmp->next;
		}
	}
	return (env);
}

void	execute_export(t_token *token, t_env *env)
{
	env = ft_export(token, env);
}
