/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:46:48 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/10 16:27:10 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//THE FT_TOKENIZER FUNCTION
//This function takes a string as an argument and returns a linked list of tokens.
//The tokens are separated by spaces.
//The tokens are of type 0 if they are a command, 1 if they are a redirection, 2 if they are a pipe, 3 if they are a semicolon, 4 if they are a variable, 5 if they are a string.
//we are using differentiation and the redirecting to different functions to use ft_lstadd_back in the different cases.

t_token	*ft_tokenizer(char *str, t_env *env)
{
	t_token	*token;
	int		i;
	int		j;
	int		isbeginning;

	i = 0;
	token = NULL;
	isbeginning = 1;
	while (str[i])
	{
		j = i;
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		else if (str[i] == '>' || str[i] == '<')
		{
			token = ft_redir(str, &i, token);
			isbeginning = 0;
		}
		else if (str[i] == '|')
		{
			token = ft_pipe(str, &i, token);
			isbeginning = 1;
		}
		else if (str[i] == '$')
		{
			token = ft_var(str, &i, token, env);
			isbeginning = 0;
		}
		else if (str[i] == '\'')
		{
			token = ft_squote(str, &i, token);
			isbeginning = 0;
		}
		else if (str[i] == '\"')
		{
			token = ft_dquote(str, &i, token);
			isbeginning = 0; 
		}
		else if (str[i] == ';')
		{
			token = ft_semicolon(str, &i, token);
			isbeginning = 1;
		}
		else
		{
			if (isbeginning == 1)
			{
				token = ft_cmd(str, &i, token);
				isbeginning = 0;
			}
			else
				token = ft_str(str, &i, token);
		}
		if (j == i)
			return (NULL);
	}
	return (token);
}

//change types according to redirection position (as the first token or not) in the command
//if it's the first token then the second token should be an argument and the third one should be a command
void	re_tokenize(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT
			|| tmp->type == REDIR_APPEND)
		{
			if (tmp->prev == NULL)
			{
				tmp->type = ARG;
				tmp->next->type = CMD;
			}
		}
		else if (tmp->type == HEREDOC)
		{
			if (tmp->prev == NULL)
			{
				tmp->type = CMD;
				tmp->next->type = ARG;
			}
		}
		tmp = tmp->next;
	}
}

void	lowerize_builtins(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (ft_strcmp1(tmp->value, "pwd") == 0)
			tmp->value = lower_pwd(tmp->value);
		if (ft_strcmp1(tmp->value, "env") == 0)
			tmp->value = lower_env(tmp->value);
		if (ft_strcmp1(tmp->value, "echo") == 0)
			tmp->value = lower_echo(tmp->value);
		tmp = tmp->next;
	}
}

int	ft_parse(char *line, t_env *env)
{
	t_token	*token;

	// (void)line;
	// (void)env;
	if (ft_check_syntax(line) == 0) // Check for no syntax error
	{
		//removed assign type to use the ft_tokenizer function
		token = ft_tokenizer(line, env);
		re_tokenize(token);
		redir_type(token);
		expand_dq(token, env);
		lowerize_builtins(token);
		if((check_args(token)) == 0)
		{
			printf("Syntax error\n");
			return (1); // Return an error code
		}
		// int		i;
		// t_token	*tmp;
		// i = 0;
		// tmp = token;
		// while (tmp)
		// {
		// 	printf("token %d: %s\n", i, tmp->value);
		// 	printf("token type: %s\n", tmp->type);
		// // 	// if (i > 0 && tmp->prev != NULL) // Check if tmp->prev is not NULL
		// // 	// 	printf("prev token %d: %s\n", i, tmp->prev->value);
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
