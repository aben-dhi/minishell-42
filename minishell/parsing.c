/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:46:48 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/09/29 17:38:10 by aben-dhi         ###   ########.fr       */
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
		else if (str[i] == '$')
			token = ft_var(str, &i, token);
		else if (str[i] == '\'')
			token = ft_squote(str, &i, token);
		else if (str[i] == '\"')
			token = ft_dquote(str, &i, token);
		else
			token = ft_str(str, &i, token);
		if (j == i)
			return (NULL);
	}
	return (token);
}
//include the check for syntax function in here
int ft_parse(char *line)
{
    t_token *token;
    int i;

    i = 0;
    if (ft_check_syntax(line) == 0) // Check for no syntax error
    {
        token = ft_tokenizer(line);
        while (token)
        {
            printf("token %d: %s\n", i, token->value);
			printf("token type: %d\n", token->type);
            token = token->next;
            i++;
        }
    }
    else
    {
        printf("Syntax error\n");
        return (1); // Return an error code
    }
    return (0); // No error
}
