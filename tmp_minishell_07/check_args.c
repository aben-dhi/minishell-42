/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 20:33:54 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/04 22:30:19 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check if the args are valid (there shouldn't be two pipes or two semicolons in a row) there shouldn't be a pipe or a semicolon at the end of the line
//there shouldn't be a pipe or a semicolon at the beginning of the line and there shouldn't be a pipe or a semicolon after a redirection.
//there shouldn't be a redirection after a redirection. there shouldn't be a redirection at the beginning of the line.
//there shouldn't be a redirection at the end of the line. there shouldn't be two consecutive commands not separated by a pipe or a semicolon.

int	check_args(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == PIPE || tmp->type == SEMICOLON)
		{
			if (tmp->next == NULL)
				return (0);
			if (tmp->prev == NULL)
				return (0);
			if (tmp->next->type == PIPE || tmp->next->type == SEMICOLON)
				return (0);
		}
		if (tmp->type == REDIR)
		{
			if (tmp->next == NULL)
				return (0);
			if (tmp->next->type == REDIR)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
//A function that puts pwd command in lowercase whatever its initial case is.
char	*lower_pwd(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'P')
			str[i] = 'p';
		if (str[i] == 'W')
			str[i] = 'w';
		if (str[i] == 'D')
			str[i] = 'd';
		i++;
	}
	return (str);
}

//a function that comapare whther the letter are the same even if they are upper or lower case.
int	comp(char c1, char c2)
{
	if (c1 == c2)
		return (0);
	if (c1 == c2 + 32)
		return (0);
	if (c1 == c2 - 32)
		return (0);
	return (1);
}

//a function that compares two strings even if they are in different cases.
int	ft_strcmp1(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && comp(s1[i], s2[i]) == 0)
		i++;
	return (comp(s1[i], s2[i]));
}

char	*lower_env(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'E')
			str[i] = 'e';
		if (str[i] == 'N')
			str[i] = 'n';
		if (str[i] == 'V')
			str[i] = 'v';
		i++;
	}
	return (str);
}

char	*lower_echo(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'E')
			str[i] = 'e';
		if (str[i] == 'C')
			str[i] = 'c';
		if (str[i] == 'H')
			str[i] = 'h';
		if (str[i] == 'O')
			str[i] = 'o';
		i++;
	}
	return (str);
}