/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:47:39 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/01 15:46:16 by aben-dhi         ###   ########.fr       */
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