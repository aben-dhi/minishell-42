/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:47:39 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/09/26 16:18:32 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//a function that treats the expand stuff

char	*expand(char *str, t_env *env)
{
	char	*new;
	char	*tmp;
	char	*tmp2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == '$')
		{
			tmp = ft_substr(str, 0, i);
			tmp2 = ft_substr(str, i + 1, ft_strlen(str) - i);
			new = ft_strjoin(tmp, get_env(env, tmp2));
			free(tmp);
			free(tmp2);
			return (new);
		}
		i++;
	}
	return (str);
}