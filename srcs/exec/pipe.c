/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:10:22 by ddecourt          #+#    #+#             */
/*   Updated: 2021/12/01 18:41:43 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pipe(t_parsing *params, char **envp)
{
	int pipe_fd[2];
	
	params->fd_stdin = dup(STDIN);
	params->fd_stdout = dup(STDOUT);
	pipe(pipe_fd);
	if (params->pipe == 0 && params->next->pipe != 0)
	{
		dup2(pipe_fd[1], STDOUT);
		ft_exec(params, envp);
		dup2(pipe_fd[0], STDIN);
		dup2(params->fd_stdout, STDOUT);
		ft_exec(params->next, envp);
		dup2(params->fd_stdin, STDIN);
		dup2(params->fd_stdout, STDOUT);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		
		return (1);
	}
	return (0);
}