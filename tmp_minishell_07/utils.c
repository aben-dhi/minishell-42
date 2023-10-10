/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:17:22 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/06 00:51:45 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arr(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (array[i] != NULL)
			free(array[i]);
		i++;
	}
	free(array);
}

int	find_in_list(t_token *token, char *to_find)
{
	t_token		*t_tmp;

	t_tmp = token;
	while (t_tmp)
	{
		if (ft_strcmp(t_tmp->value, to_find) == 0)
			return (0);
		t_tmp = t_tmp->next;
	}
	return (1);
}
