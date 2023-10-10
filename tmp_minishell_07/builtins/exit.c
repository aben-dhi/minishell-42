/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:08:35 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/10 16:10:53 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	ft_exit(t_token *token)
// {
// 	int		i;
// 	int		j;
// 	char	*str;

// 	i = 0;
// 	j = 0;
// 	str = token->value;
// 	while (str[i])
// 	{
// 		if (ft_isdigit(str[i]))
// 			j++;
// 		i++;
// 	}
// 	if (j == i)
// 		exit(ft_atoi(str));
// 	else
// 	{
// 		ft_putstr_fd("exit\n", 1);
// 		ft_putstr_fd("minishell: exit: ", 1);
// 		ft_putstr_fd(str, 1);
// 		ft_putstr_fd(": numeric argument required\n", 1);
// 		exit(255);
// 	}
// }