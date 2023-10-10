/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:58:05 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/09 17:26:22 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//we are going to use the ft_lstadd_back function to add the tokens to the linked list.
//there is chi haja smitha 2> as in redirect to the STDOUT, I need to add it as  a condition in the ft_redir function.
//make sure that the double quotes and single quotes are closed and parenthese are closed.
//make sure that the redirections are correct.
//make sure that the pipes are correct.

int	ft_check_syntax(char *line)
{
	int	i;
	int	squote;
	int	dquote;
	int	parenthese;

	i = 0;
	squote = 0;
	dquote = 0;
	parenthese = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			squote = !squote;
		if (line[i] == '\"' && squote == 1)
		{
			dquote = !dquote;
			squote = 0;
		}
		else if (line[i] == '\"')
			dquote = !dquote;
		if (line[i] == '(')
			parenthese++;
		if (line[i] == ')')
		{
			if (parenthese == 0 && !squote && !dquote)
				return (1);
			parenthese--;
		}
		i++;
	}
	if (squote == 1 || dquote == 1)
		return (1);
	if (parenthese == 1)
		return (1);
	if (parenthese < 0)
		return (1);
	return (0);
}
