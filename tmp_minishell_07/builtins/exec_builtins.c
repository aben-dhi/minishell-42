/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 20:02:55 by htouil            #+#    #+#             */
/*   Updated: 2023/10/07 17:45:00 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_builtins(t_token *token, t_env *env)
{
	if (!token)
		return ;
	else if (find_in_list(token, "env") == 0)
		execute_env(env);
	else if (find_in_list(token, "export") == 0)
		execute_export(token, env);
	else if (find_in_list(token, "unset") == 0)
		execute_unset(token, env);
	else if (find_in_list(token, "pwd") == 0)
		execute_pwd(token, env);
	else if (find_in_list(token, "cd") == 0)
		execute_cd(token, env);
	else if (find_in_list(token, "echo") == 0)
		execute_echo(token);
}
