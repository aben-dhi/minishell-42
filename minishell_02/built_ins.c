/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 20:02:55 by htouil            #+#    #+#             */
/*   Updated: 2023/10/02 20:04:29 by aben-dhi         ###   ########.fr       */
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

t_env	*ft_export(t_token *token, t_env *env)
{
	t_env	*new;
	t_env	*e_tmp;
	t_token	*t_tmp;
	char	**arg;

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
			e_tmp = env;
			while (e_tmp)
			{
				if (ft_strcmp(e_tmp->envar, arg[0]) == 0)
				{
					e_tmp->enval = ft_strcpy(arg[1]);
					break ;
				}
				if ((ft_strcmp(e_tmp->envar, arg[0]) != 0)
					&& e_tmp->next == NULL)
				{
					new = malloc(sizeof(t_env));
					new->envar = ft_strcpy(arg[0]);
					new->enval = ft_strcpy(arg[1]);
					new->next = NULL;
					ft_lstadd_back2(&e_tmp, new);
					break ;
				}
				e_tmp = e_tmp->next;
			}
			free_arr(arg);
			t_tmp = t_tmp->next;
		}
	}
	return (env);
}

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
				free_node(x);
				break ;
			}
			else
				e_tmp = e_tmp->next;
		}
		t_tmp = t_tmp->next;
	}
	return (env);
}

void	ft_pwd(t_env *env)
{
	t_env	*e_tmp;

	e_tmp = env;
	while (e_tmp)
	{
		if (ft_strcmp(e_tmp->envar, "PWD") == 0)
		{
			printf("%s\n", e_tmp->enval);
			break ;
		}
		e_tmp = e_tmp->next;
	}
}

void	execute_builtins(t_token *token, t_env *env)
{
	if (!token)
		return ;
	else if (ft_strcmp(token->value, "env") == 0)
		ft_env(env);
	else if (ft_strcmp(token->value, "export") == 0)
		env = ft_export(token, env);
	else if (ft_strcmp(token->value, "unset") == 0)
		env = ft_unset(token, env);
	else if (ft_strcmp(token->value, "pwd") == 0)
		ft_pwd(env);
}
