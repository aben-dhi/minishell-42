/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 03:44:54 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/15 03:46:03 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//ft_caloc is a function that allocates memory and fills it with zeros.
char	*ft_calloc(int size, int len)
{
	char    *str;
	int        i;

	i = 0;
	str = malloc(size * len);
	if (!str)
		return (NULL);
	while (i < size * len)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}

char    *ft_realloc(char *str, int size)
{
    char    *tmp;
    int        old_size;

    if (str == NULL)
    {
        return (ft_calloc(size, 1));
    }
    else if (size == 0)
    {
        free(str);
        return (NULL);
    }
    else
    {
        old_size = ft_strlen(str) + 1;
        tmp = ft_calloc(size, 1);
        ft_strlcpy(tmp, str, old_size);
        free(str);
        return (tmp);
    }
}