/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htouil <htouil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:46:48 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/09/26 22:36:12 by htouil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//THE FT_TOKENIZER FUNCTION
//This function takes a string as an argument and returns a linked list of tokens.
//The tokens are separated by spaces.
//The tokens are of type 0 if they are a command, 1 if they are a redirection, 2 if they are a pipe, 3 if they are a semicolon, 4 if they are a variable, 5 if they are a string.
//we are using differentiation and the redirecting to different functions to use ft_lstadd_back in the different cases.

t_token	*ft_tokenizer(char *str)
{
	t_token	*token;
	int		i;
	int		j;

	i = 0;
	token = NULL;
	while (str[i])
	{
		j = i;
		if (str[i] == ' ')
			i++;
		else if (str[i] == '>' || str[i] == '<')
			token = ft_redir(str, &i, token);
		else if (str[i] == '|')
			token = ft_pipe(str, &i, token);
		else if (str[i] == ';')
			token = ft_semicolon(str, &i, token);
		else if (str[i] == '$')
			token = ft_var(str, &i, token);
		else
			token = ft_str(str, &i, token);
		if (j == i)
			return (NULL);
	}
	return (token);
}

int	ft_parse(char *line)
{
	t_token	*token;
	int		i;

	i = 0;
	token = ft_tokenizer(line);
	while (token)
	{
		printf("token %d: %s\n", i, token->value);
		token = token->next;
		i++;
	}
	return (0);
}
