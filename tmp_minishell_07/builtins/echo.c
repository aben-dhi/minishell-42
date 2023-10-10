/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:33:48 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/07 19:06:29 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_l(char *str1, char l)
{
	int	i;

	i = 0;
	if (str1[i] == '-')
	{
		i++;
		while (str1[i])
		{
			if (str1[i] != l)
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}

char	*ft_echo(t_token *token)
{
	t_token	*t_tmp;
	char	*echoing;

	echoing = NULL;
	if (ft_strcmp(token->value, "echo") == 0)
	{
		if (token->next == NULL)
			return ("\n");
		else if (ft_is_l(token->next->value, 'n') == 0 && token->next->next == NULL)
			return ("");
		else if (ft_is_l(token->next->value, 'n') == 0 && token->next->next != NULL)
		{
			t_tmp = token->next->next;
			while (t_tmp && ft_strcmp(t_tmp->value, ">") != 0 && ft_strcmp(t_tmp->value, ">>") != 0 && ft_strcmp(t_tmp->value, "<") != 0)
			{
				echoing = ft_strjoin(echoing, t_tmp->value);
				if (t_tmp->next && ft_strcmp(t_tmp->next->value, ">") != 0 && ft_strcmp(t_tmp->next->value, ">>") != 0)
					echoing = ft_strjoin(echoing, " ");
				t_tmp = t_tmp->next;
			}
		}
		else if (ft_is_l(token->next->value, 'n') != 0)
		{
			t_tmp = token->next;
			while (t_tmp && ft_strcmp(t_tmp->value, ">") != 0 && ft_strcmp(t_tmp->value, ">>") != 0 && ft_strcmp(t_tmp->value, "<") != 0)
			{
				echoing = ft_strjoin(echoing, t_tmp->value);
				if (t_tmp->next && ft_strcmp(t_tmp->next->value, ">") != 0 && ft_strcmp(t_tmp->next->value, ">>") != 0)
					echoing = ft_strjoin(echoing, " ");
				t_tmp = t_tmp->next;
			}
			echoing = ft_strjoin(echoing, "\n");
		}
	}
	else if (ft_strcmp(token->value, ">") == 0 || ft_strcmp(token->value, ">>") == 0)
	{
		t_tmp = token->next->next;
		echoing = ft_echo(t_tmp);
	}
	else
	{
		ft_putstr_fd(token->value, 2);
		ft_putstr_fd(" : Command not found\n", 2);
		return (NULL);
	}
	return (echoing);
}

void	execute_echo(t_token *token)
{
	char	*echo_str;
	t_token	*t_tmp;
	int		flag;

	echo_str = ft_echo(token);
	if (!echo_str)
		return ;
	flag = 0;
	t_tmp = token;
	while (t_tmp)
	{
		if (t_tmp->type == REDIR_OUT)
		{
			ft_redir_out(t_tmp->next->value, echo_str);
			flag = 1;
		}
		else if (t_tmp->type == REDIR_APPEND)
		{
			ft_redir_append(t_tmp->next->value, echo_str);
			flag = 1;
		}
		else if (t_tmp->type == REDIR_IN)
			flag = 0;
		t_tmp = t_tmp->next;
	}
	if (flag == 0)
		printf("%s", echo_str);
	free(echo_str);//recheck if echo_str needs to be freed here.
}
