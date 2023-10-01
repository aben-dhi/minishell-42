/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htouil <htouil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 20:02:55 by htouil            #+#    #+#             */
/*   Updated: 2023/09/30 22:54:23 by htouil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		new->value = getenv(new->envar);
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
		printf("%s=%s\n", e_tmp->envar, e_tmp->value);
		e_tmp = e_tmp->next;
	}
}

t_env	*ft_export(t_token *token, t_env *env)
{
	// t_env	*new;
	t_env	*e_tmp;
	char	**arg;

	e_tmp = env;
	if (token->next == NULL) //must check that export function has no args
	{
		while (e_tmp)
		{
			printf("declare -x %s=\"%s\"\n", e_tmp->envar, e_tmp->value);
			e_tmp = e_tmp->next;
		}
	}
	else //with args
	{
		arg = ft_split(token->next->value, '=');
		while (e_tmp)
		{
			if (ft_strcmp(e_tmp->envar, arg[0]) == 0)
				e_tmp->value = arg[1];
			e_tmp = e_tmp->next;
		}
		// if (ft_strcmp(e_tmp->envar, arg[0]) != 0)
		// {
			
		// }
	}
	return (env);
}

void	execute_builtins(t_token *token, t_env *env)
{
	if (ft_strcmp(token->value, "env") == 0)
		ft_env(env);
	if (ft_strcmp(token->value, "export") == 0)
		env = ft_export(token, env);
}
