/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_fcts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htouil <htouil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 00:06:21 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/05 22:53:20 by htouil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_out(char *outfile, char *reded_str)
{
	int	fd;

	fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(outfile);
		return ;
	}
	ft_putstr_fd(reded_str, fd);
	close(fd);
}

void	ft_redir_append(char *outfile, char *reded_str)
{
	int	fd;

	fd = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(outfile);
		return ;
	}
	ft_putstr_fd(reded_str, fd);
	close(fd);
}

// void	create_file_wnl()
