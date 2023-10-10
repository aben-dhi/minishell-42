/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:49:31 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/06 01:07:25 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//we need to give the main as a reference the envp to use it in the expand function.
int	main(int ac, char **av, char **envp)
{
	char	*line;
	// char	**tokens;
	t_env	*env;

	(void)ac;
	(void)av;
	env = ft_env_fill(envp);
	while (1)
	{
		line = readline(CYAN"minishell $> "CX);
		if (!line)
			break ;
		else if (line[0] != '\0')
			add_history(line);
			//removed split to use the ft_parse function
		// tokens = ft_split(line, ' ');
		// while (*tokens)
		// 	printf("%s.\n", *tokens++);
		ft_parse(line, env);
		free(line);
	}
	return (0);
}
