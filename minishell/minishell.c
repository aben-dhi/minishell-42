/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htouil <htouil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:49:31 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/09/26 22:36:06 by htouil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//we need to give the main as a reference the envp to use it in the expand function.
int	main(void)
{
	char	*line;

	// envp = getenvp(envp);
	while (1)
	{
		line = readline(GREY"minishell $> "CX);
		if (!line)
			break ;
		else if (line[0] != '\0')
			add_history(line);
		ft_parse(line);
		free(line);
	}
	return (0);
}
