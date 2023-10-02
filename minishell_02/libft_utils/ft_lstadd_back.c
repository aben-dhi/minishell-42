/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htouil <htouil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:58:31 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/01 22:13:34 by htouil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_node(t_env *env)
{
	if (env->envar)
		free(env->envar);
	if (env->enval)
		free(env->enval);
	free(env);
}

t_token	*ft_lstlast1(t_token *lst)
{
	t_token	*last;

	last = lst;
	if (last)
		while (last->next)
			last = last->next;
	return (last);
}

void	ft_lstadd_back1(t_token **lst, t_token *new)
{
	t_token	*last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_lstlast1(*lst);
			last->next = new;
			new->prev = last;
		}
		else
		{
			*lst = new;
			new->prev = NULL;
		}
	}
}

t_env	*ft_lstlast2(t_env *lst)
{
	t_env	*last;

	last = lst;
	if (last)
		while (last->next)
			last = last->next;
	return (last);
}

void	ft_lstadd_back2(t_env **lst, t_env *new)
{
	t_env	*last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_lstlast2(*lst);
			last->next = new;
			new->prev = last;
		}
		else
		{
			*lst = new;
			new->prev = NULL;
		}
	}
}
