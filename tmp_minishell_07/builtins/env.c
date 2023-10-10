/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:19:59 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/07 16:41:06 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_env_fill(char **envp)
{
	t_env	*env;
	t_env	*new;
	int		i;
	int		j;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		new = malloc(sizeof(t_env));
		new->envar = ft_substr(envp[i], 0, j);
		new->enval = getenv(new->envar);
		new->next = NULL;
		ft_lstadd_back2(&env, new);
		i++;
	}
	return (env);
}

void	ft_env(t_env *env)
{
	t_env	*e_tmp;

	e_tmp = env;
	while (e_tmp)
	{
		printf("%s=%s\n", e_tmp->envar, e_tmp->enval);
		e_tmp = e_tmp->next;
	}
}

void	execute_env(t_env *env)
{
	ft_env(env);
}
