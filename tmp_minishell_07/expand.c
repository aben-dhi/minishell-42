/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:47:39 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/16 00:21:39 by aben-dhi         ###   ########.fr       */
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
			else
				token->value = ft_strdup("");
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
				else
					token->value = ft_strdup("");
				i++;
			}
		}
		i++;
	}
	return (token->value);
}

// char *expand_in_dq(char *str, t_env *env) {
//     char *expanded = ft_strdup(""); // Initialize to an empty string
//     size_t len = 0;
//     size_t i = 0;
// 	size_t k = 0;

//     while (str[i]) {
//         if (str[i] == '$' && ft_isalnum(str[i + 1])) {
//             i++;
//             size_t j = i;
//             while (str[i] && (ft_isalnum(str[i]) || str[i] == '_')) {
//                 i++;
//             }

//             char *var = ft_substr(str, j, i - j);
//             char *value = get_env(env, var);

//             if (value) {
//                 expanded = ft_strjoin_realloc(expanded, value, &len);
//             } else {
//                 expanded = ft_strjoin_realloc(expanded, var, &len);
//             }

//             free(var);
//         } else {
//             expanded = ft_strjoin_realloc(expanded, &str[i], &len);
//             i++;
//         }
//     }

//     return expanded;
// }

char *expand_in_dq(char *str, t_env *env) {
    char *expanded = ft_strdup(""); // Initialize to an empty string
    size_t len = 0;
    size_t i = 0;
    size_t k = 0; // Initialize k to 0

    while (str[i]) {
        if (str[i] == '$' && ft_isalnum(str[i + 1])) {
            i++;
            size_t j = i;
            while (str[i] && (ft_isalnum(str[i]) || str[i] == '_')) {
                i++;
            }

            char *var = ft_substr(str, j, i - j);
            char *value = get_env(env, var);

            if (value) {
                // Extract the part between k and j and append value with spaces
                char *part = ft_substr(str, k, j - k - 1);
                expanded = ft_strjoin_realloc(expanded, part, &len);
                free(part);
                expanded = ft_strjoin_realloc(expanded, value, &len);
            } else {
                // Append the entire substring
                char *sub = ft_substr(str, k, i - k);
                expanded = ft_strjoin_realloc(expanded, sub, &len);
                free(sub);
            }

            free(var);
            k = i; // Update k to the current position
        } else if (str[i] == ' ') {
            // Append the part between k and i (space) with spaces
            char *part = ft_substr(str, k, i - k);
            expanded = ft_strjoin_realloc(expanded, part, &len);
            free(part);

            // Check for consecutive spaces
            while (str[i] == ' ') {
                expanded = ft_strjoin_realloc(expanded, " ", &len);
                i++;
            }

            k = i; // Update k to the current space position
        }
        i++;
    }

    // Append any remaining characters
    if (k < i) {
        char *remaining = ft_substr(str, k, i - k);
        expanded = ft_strjoin_realloc(expanded, remaining, &len);
        free(remaining);
    }

    return expanded;
}

void expand_dq(t_token *token, t_env *env) {
    t_token *tmp = token;

    while (tmp) {
        if (tmp->type == DQUOTE) {
            char *expanded_string = expand_in_dq(tmp->value, env);

            if (expanded_string) {
                free(tmp->value);
                tmp->value = expanded_string;
            }
        }

        tmp = tmp->next;
    }
}


	// t_token	*tmp;
	// char	*new_value;

	// tmp = token;
	// while (tmp)
	// {
	// 	if (tmp->type == DQUOTE && ft_strchr(tmp->value, '$') != NULL)
	// 	{
	// 		new_value = expand2(tmp->value, env, tmp);
	// 		if (new_value)
	// 			tmp->value = ft_strcpy(new_value);
	// 	}
	// 	tmp = tmp->next;
	// }
// void	expand_dq(t_token *token, t_env *env)
// {
// 	t_token	*tmp;

// 	tmp = token;
// 	while (tmp)
// 	{
// 		if (tmp->type == DQUOTE)
// 		{
// 			// Use a temporary string to store the expanded value
// 			char *new_value = expand(tmp->value, env, tmp);

// 			// Check if the expansion was successful
// 			if (new_value)
// 			{
// 				// Replace the token's value with the expanded value
// 				free(tmp->value);
// 				tmp->value = new_value;
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// }
//we're gonna use ft_substr (create an array of strings that contains the value of the token split by spaces using substr and all of this is in a temporary variable) and then expand them if they are expandable and then join them again. we need to perserve the initial string though in case there were spaces in the end of the line or the beginning of the line.
