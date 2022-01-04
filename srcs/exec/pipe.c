/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:10:22 by ddecourt          #+#    #+#             */
/*   Updated: 2021/12/27 21:22:47 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pipe_in(t_parsing *params, char **envp, int pipe_out, int pipe_in)
{
	close(pipe_out);
	dup2(pipe_in, STDOUT);
	if (params->type == 0)
		ft_exec(params, envp);
	else
		ft_exec_redir(params, envp);
	return (0);
}

t_parsing	*ft_pipe(t_parsing *params, char **envp)
{
	int	pipe_fd[2];
	int	pid;

	params->fd_stdin = dup(STDIN);
	params->fd_stdout = dup(STDOUT);
	pid = fork();
	ft_disable(pid);
	pipe(pipe_fd);
	if (pid == 0)
		ft_pipe_in(params, envp, pipe_fd[0], pipe_fd[1]);
	waitpid(-1, 0, 0);
	if (pid != 0)
	{
		//close(pipe_fd[0]);
		close(pipe_fd[1]);
		dup2(params->fd_stdout, STDOUT);
	}
	waitpid(-1, 0, 0);
	if (params->next)
		params = params->next;
	ft_launch_signal();
	return (params);
}
