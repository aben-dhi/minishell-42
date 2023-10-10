/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:47:39 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/07 18:05:06 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_env *env, char *smtg)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->envar, smtg) == 0)
			return (tmp->enval);
		tmp = tmp->next;
	}
	return (NULL);
}

//a function that expands the variables in the string and puts the result in token->value if it is expandable.

char	*expand(char *str, t_env *env, t_token *token)
{
	char	*new;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = NULL;
	while (str[i])
	{
		if (str[i] == '$' && ft_isalnum(str[i + 1]))
		{
			i++;
			j = i;
			while (str[i] && ft_isalnum(str[i]))
				i++;
			new = ft_substr(str, j, i - j);
			char *value = get_env(env, new);
			if (value)
			{
				// tmp = ft_strjoin(token->value, value);
				free(token->value);
				token->value = ft_strdup(value);
			}
			// else
			// 	token->value = ft_strjoin(token->value, "");
			free(new);
			j = i;
		}
		else if (str[i] == '$' && str[i + 1] == '{')
		{
			i += 2; // Skip '$' and '{'
			j = i;
			while (str[i] && str[i] != '}')
				i++;
			if (str[i] == '}')
			{
				new = ft_substr(str, j, i - j);
				char *value = get_env(env, new);
				free(new);

				if (value)
				{
					// tmp = ft_strjoin(token->value, value);
					free(token->value);
					token->value = ft_strdup(value);
				}
				i++;
			}
		}
		i++;
	}
	return (token->value);
}

// char *expand(char *str, t_env *env, t_token *token)
// {
// 	char *new;
// 	char *tmp;
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	tmp = NULL;
// 	while (str[i])
// 	{
// 		if (str[i] == '$' && str[i + 1] == '{')
// 		{
// 			i += 2; // Skip '$' and '{'
// 			j = i;
// 			while (str[i] && str[i] != '}')
// 				i++;
// 			if (str[i] == '}')
// 			{
// 				new = ft_substr(str, j, i - j);
// 				char *value = get_env(env, new);
// 				free(new);

// 				if (value)
// 				{
// 					tmp = ft_strjoin(token->value, value);
// 					free(token->value);
// 					token->value = tmp;
// 				}
// 				// else
// 				// {
// 				// 	// If the variable is not found, include the original "${...}" in the result
// 				// 	tmp = ft_strjoin(token->value, "${");
// 				// 	tmp = ft_strjoin(tmp, new);
// 				// 	tmp = ft_strjoin(tmp, "}");
// 				// 	free(token->value);
// 				// 	token->value = tmp;
// 				// }

// 				i++; // Skip '}'
// 			}
// 		}
// 		i++;
// 	}
// 	return (token->value);
// }

//a function that expands the variables tha are in double quotes if it is expandable.
// void	expand_dq(t_token *token, t_env *env)
// {
// 	char	*new;
// 	t_token	*tmp;
// 	int		i;

// 	i = 0;
// 	tmp = token;
// 	while (tmp)
// 	{
// 		if (tmp->type == DQUOTE)
// 		{
// 			if (ft_strcmp(&tmp->value[i], "\"") == 0 && ft_strcmp(&tmp->value[i + 1], "$") == 0)
// 			{
// 				new = tmp->value;
// 				new = ft_strtrim(new, "\"");
// 				free(tmp->value);
// 				tmp->value = new;
// 				tmp->value = expand(tmp->value, env, tmp);
// 			}
// 			else
// 			{
// 				new = tmp->value;
// 				new = ft_strtrim(new, "\"");
// 				free(tmp->value);
// 				tmp->value = new;
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// }

//if the token is a double quote, check if the next token is a variable, if it is, expand it.
void	expand_dq(t_token *token, t_env *env)
{
	t_token	*tmp;
	char	*new_value;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == DQUOTE && ft_strchr(tmp->value, '$') != NULL)
		{
			new_value = expand(tmp->value, env, tmp);
			if (new_value)
				tmp->value = ft_strcpy(new_value);
		}
		tmp = tmp->next;
	}
}