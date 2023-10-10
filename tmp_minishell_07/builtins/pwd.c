/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:31:20 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/07 16:52:11 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_cmd_preceded(t_token *token, char *cmd)
{
	t_token	*t_tmp;

	t_tmp = token;
	while (t_tmp && ft_strcmp(t_tmp->value, cmd) != 0)
		t_tmp = t_tmp->next;
	if (!t_tmp->prev || t_tmp->prev->type == FILE)
		return (0);
	return (1);
}

char	*ft_pwd(t_token *token, t_env *env)
{
	t_env	*e_tmp;
	t_token	*t_tmp;

	if (is_cmd_preceded(token, "pwd") == 1)
	{
		t_tmp = token;
		while (t_tmp && ft_strcmp(t_tmp->value, "pwd") != 0)
			t_tmp = t_tmp->next;
		if (t_tmp->prev->type == FILE)
			ft_putstr_fd(token->value, 2);
		else
			ft_putstr_fd(t_tmp->prev->value, 2);
		ft_putstr_fd(" : Command not found\n", 2);
		return (NULL);
	}
	else
	{
		e_tmp = env;
		while (e_tmp)
		{
			if (ft_strcmp(e_tmp->envar, "PWD") == 0)
				return (e_tmp->enval);
			e_tmp = e_tmp->next;
		}
	}
	return (NULL);
}

void	execute_pwd(t_token *token, t_env *env)
{
	char	*pwd_str;
	t_token	*t_tmp;
	int		flag;

	pwd_str = ft_pwd(token, env);
	if (is_cmd_preceded(token, "pwd") == 1)
	{
		if (find_in_list(token, ">") == 1 && find_in_list(token, ">>") == 1)
			return ;
		else if (find_in_list(token, ">") == 0
			|| find_in_list(token, ">>") == 0)
		{
			flag = 0;
			t_tmp = token;
			while (t_tmp)
			{
				if (t_tmp->type == REDIR_OUT)
				{
					ft_redir_out(t_tmp->next->value, "");
					flag = 1;
				}
				else if (t_tmp->type == REDIR_APPEND)
				{
					ft_redir_append(t_tmp->next->value, "");
					flag = 1;
				}
				else if (t_tmp->type == REDIR_IN)
					flag = 1;
				t_tmp = t_tmp->next;
			}
			if (flag == 0)
				printf("%s\n", pwd_str);
		}
	}
	else if (is_cmd_preceded(token, "pwd") == 0)
	{
		if (find_in_list(token, ">") == 0 || find_in_list(token, ">>") == 0)
		{
			flag = 0;
			t_tmp = token;
			while (t_tmp)
			{
				if (t_tmp->type == REDIR_OUT)
				{
					ft_redir_out(t_tmp->next->value, pwd_str);
					flag = 1;
				}
				else if (t_tmp->type == REDIR_APPEND)
				{
					ft_redir_append(t_tmp->next->value, pwd_str);
					flag = 1;
				}
				else if (t_tmp->type == REDIR_IN)
					flag = 0;
				t_tmp = t_tmp->next;
			}
			if (flag == 0)
				printf("%s", pwd_str);
		}
		else if (find_in_list(token, ">") == 1
			|| find_in_list(token, ">>") == 1)
			printf("%s\n", pwd_str);
	}
}
