/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:32:42 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/07 16:53:41 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_update_pwd(t_env *env, char *old)
{
	t_env	*e_tmp;

	e_tmp = env;
	while (e_tmp)
	{
		if (ft_strcmp(e_tmp->envar, "OLDPWD") == 0)
		{
			// free(e_tmp->enval);
			e_tmp->enval = ft_strcpy(old);
		}
		if (ft_strcmp(e_tmp->envar, "PWD") == 0)
		{
			// free(e_tmp->enval);
			e_tmp->enval = malloc(2000 * sizeof(char));
			e_tmp->enval = getcwd(e_tmp->enval, 2000);
		}
		e_tmp = e_tmp->next;
	}
	return (env);
}

t_env	*ft_cd(t_token *token, t_env *env)
{
	t_env	*e_tmp;
	char	*old;

	old = malloc(2000 * sizeof(char));
	if (!old)
		exit (1);
	old = getcwd(old, 2000);
	if (ft_strcmp(token->value, "cd") != 0)
	{
		ft_putstr_fd(token->value, 2);
		ft_putstr_fd(" : Command not found\n", 2);
		return (NULL);
	}
	if (token->next == NULL)
	{
		e_tmp = env;
		while (e_tmp)
		{
			if (ft_strcmp(e_tmp->envar, "HOME") == 0)
			{
				if (chdir(e_tmp->enval) == -1)
				{
					write (2, "cd: ", 4);
					perror("HOME");
				}
				env = ft_update_pwd(env, old);
				break ;
			}
			e_tmp = e_tmp->next;
		}
	}
	else if (token->next != NULL)
	{
		if (chdir(token->next->value) == -1)
		{
			write (2, "cd: ", 4);
			perror(token->next->value);
		}
		env = ft_update_pwd(env, old);
	}
	free (old);
	return (env);
}

void	execute_cd(t_token *token, t_env *env)
{
	env = ft_cd(token, env);
}
