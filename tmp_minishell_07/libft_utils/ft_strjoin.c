/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 12:48:31 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/15 03:44:42 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *str1, char *str2)
{
	int		i;
	int		j;
	char	*joined;

	if (!str1)
	{
		str1 = malloc(1 * sizeof(char));
		str1[0] = '\0';
	}
	joined = malloc((ft_strlen(str1) + ft_strlen(str2) + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	i = -1;
	j = -1;
	while (str1[++i])
		joined[i] = str1[i];
	while (str2[++j])
		joined[i + j] = str2[j];
	joined[i + j] = '\0';
	// free (str1);
	return (joined);
}

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*new;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
// 	if (!new)
// 		return (NULL);
// 	while (s1 && s1[i])
// 	{
// 		new[i] = s1[i];
// 		i++;
// 	}
// 	while (s2 && s2[j])
// 	{
// 		new[i] = s2[j];
// 		i++;
// 		j++;
// 	}
// 	new[i] = '\0';
// 	return (new);
// }

char *ft_strjoin_realloc(char *s1, const char *s2, size_t *s1_len) {
    if (s1 == NULL) {
        return strdup(s2);
    }

    size_t s1_len_orig = *s1_len;
    size_t s2_len = strlen(s2);
    *s1_len += s2_len;

    s1 = ft_realloc(s1, *s1_len + 1);
    if (s1 == NULL) {
        // Handle memory allocation error
        return NULL;
    }

    memcpy(s1 + s1_len_orig, s2, s2_len);
    s1[*s1_len] = '\0';

    return s1;
}