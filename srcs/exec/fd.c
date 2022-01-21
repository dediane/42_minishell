/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:16:28 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/21 11:36:34 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	save_in_out(t_parsing *params)
{
	params->fd_stdin = dup(STDIN);
	params->fd_stdout = dup(STDOUT);
	return ;
}

void	set_fd(t_parsing *params, int fd)
{
	if (params->file->ftype == 2 || params->file->ftype == 3)
		dup2(fd, 1);
	if (params->file->ftype == 1)
		dup2(fd, 0);
	return ;
}

void	close_fd(t_parsing *params)
{
	if (params->heredoc == 1)
		dup2(params->fd_stdin, STDIN);
	dup2(params->fd_stdout, STDOUT);
	dup2(params->fd_stdin, STDIN);
	close(params->fd_stdin);
	close(params->fd_stdout);
	return ;
}

void	close_heredoc(int pipe_fd[2], t_parsing *params, char *line)
{
	free(line);
	dup2(pipe_fd[0], STDIN);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	params->heredoc = 1;
	return ;
}

void	print_heredoc(int pipe_fd[2], char *line)
{
	write(pipe_fd[1], line, ft_strlen(line));
	write(pipe_fd[1], "\n", 1);
	return ;
}
