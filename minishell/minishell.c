/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:49:31 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/09/29 16:46:36 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//we need to give the main as a reference the envp to use it in the expand function.
int	main(void)
{
	char	*line;

	// envp = getenv(envp);
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