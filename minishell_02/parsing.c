/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htouil <htouil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:46:48 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/01 22:43:23 by htouil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//THE FT_TOKENIZER FUNCTION
//This function takes a string as an argument and returns a linked list of tokens.
//The tokens are separated by spaces.
//The tokens are of type 0 if they are a command, 1 if they are a redirection, 2 if they are a pipe, 3 if they are a semicolon, 4 if they are a variable, 5 if they are a string.
//we are using differentiation and the redirecting to different functions to use ft_lstadd_back in the different cases.

// t_token	*ft_tokenizer(char *str)
// {
// 	t_token	*token;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	token = NULL;
// 	while (str[i])
// 	{
// 		j = i;
// 		if (str[i] == ' ')
// 			i++;
// 		if (str[i] != '>' && str[i] != '<') 
// 			token = ft_cmd(str, &i, token);
// 		else if (str[i] == '>' || str[i] == '<')
// 			token = ft_redir(str, &i, token);
// 		else if (str[i] == '|')
// 			token = ft_pipe(str, &i, token);
// 		else if (str[i] == '$')
// 			token = ft_var(str, &i, token);
// 		else if (str[i] == '\'')
// 			token = ft_squote(str, &i, token);
// 		else if (str[i] == '\"')
// 			token = ft_dquote(str, &i, token);
// 		else
// 			token = ft_str(str, &i, token);
// 		if (j == i)
// 			return (NULL);
// 	}
// 	return (token);
// }

// t_token	*ft_tokenizer(char **tokens)
// {
// 	t_token	*token;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	token = NULL;
// 	while (*tokens)
// 	{
// 		j = 0;
// 		token = ft_str(*tokens, &j, token);
// 		tokens++;
// 	}
// 	return (token);
// }
// added funtion
t_token	*ft_tokenizer(char *str, t_env *env)
{
	t_token *token;
	// t_token *prev;
	int 	i;
	int 	j;
	int 	isBeginning = 1; // Initialize as 1 to indicate the beginning of a command

	i = 0;
	token = NULL;
	// prev = NULL;
	while (str[i])
	{
		j = i;
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		else if (str[i] == '>' || str[i] == '<')
		{
			token = ft_redir(str, &i, token);
			isBeginning = 0;
		}
		else if (str[i] == '|')
		{
			token = ft_pipe(str, &i, token);
			isBeginning = 1;
		}
		else if (str[i] == '$')
		{
			token = ft_var(str, &i, token, env);
			isBeginning = 0;
		}
		else if (str[i] == '\'')
		{
			token = ft_squote(str, &i, token);
			isBeginning = 0;
		}
		else if (str[i] == '\"')
		{
			token = ft_dquote(str, &i, token);
			isBeginning = 0; 
		}
		else
		{
			if (isBeginning == 1)
			{
				token = ft_cmd(str, &i, token);
				isBeginning = 0;
			}
			else
				token = ft_str(str, &i, token);
		}
		if (j == i)
			return (NULL);
	}
	return (token);
}

//include the check for syntax function in here
// int	ft_parse(char *line, t_env *env)
// {
// 	t_token	*token;
// 	int		i;

// 	i = 0;
// 	(void)line;
// 	(void)env;
// 	if (ft_check_syntax(line) == 0) // Check for no syntax error
// 	{
// 		token = ft_tokenizer(line);
// 		// ft_assign_type(&token);
// 		while (token)
// 		{
// 			printf("token %d: %s\n", i, token->value);
// 			printf("token type: %s\n", token->type);
// 			if (i > 0)
// 				printf("prev token %d: %s\n", i, token->prev->value);
// 			token = token->next;
// 			i++;
// 		}
// 	}
// 	else
// 	{
// 		printf("Syntax error\n");
// 		return (1); // Return an error code
// 	}
// 	// execute_builtins(token, env);
// 	return (0); // No error
// }

int	ft_parse(char *line, t_env *env)
{
	t_token	*token;
	// t_token	*tmp;
	int		i;

	i = 0;
	(void)line;
	(void)env;
	if (ft_check_syntax(line) == 0) // Check for no syntax error
	{
		//removed assign type to use the ft_tokenizer function
		token = ft_tokenizer(line, env);
		// ft_assign_type(&token);
		// tmp = token;
		// while (tmp)
		// {
		// 	printf("token %d: %s\n", i, tmp->value);
		// 	printf("token type: %s\n", tmp->type);
		// 	// if (i > 0 && tmp->prev != NULL) // Check if tmp->prev is not NULL
		// 	// 	printf("prev token %d: %s\n", i, tmp->prev->value);
		// 	tmp = tmp->next;
		// 	i++;
		// }
	}
	else
	{
		printf("Syntax error\n");
		return (1); // Return an error code
	}
	execute_builtins(token, env);
	return (0); // No error
}
