/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:10:22 by ddecourt          #+#    #+#             */
/*   Updated: 2021/12/09 19:17:21 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*int	ft_pipe(t_parsing *params, char **envp)
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
}*/

int	ft_pipe_in(t_parsing *params, char **envp, int pipe_out, int pipe_in)
{
	char	*right_path;
	int		pid;
	
	right_path = get_right_path(params, envp);
	close(pipe_out);
	dup2(pipe_in, STDOUT);
	if (is_built_in(params, params->tabs[0], envp))
	{
		close(pipe_in);
		dup2(params->fd_stdout, STDOUT);
		return (0);
	}
	else
	{
		pid = fork();
		if (pid == 0)
			execve(*params->tabs, &right_path, envp);
		else
		{
			waitpid(pid, 0, 0);
			//close(pipe_in);
			//dup2(params->fd_stdout, STDOUT);
			//return (0);
		}
	}
	//ft_exec(params, envp);
	close(pipe_in);
	dup2(params->fd_stdout, STDOUT);
	return (0);
}

t_parsing	*ft_pipe(t_parsing *params, char **envp)
{
	int pipe_fd[2];
	int pid;
	//int dup_pipe[2];
	
	params->fd_stdin = dup(STDIN);
	params->fd_stdout = dup(STDOUT);
	pipe(pipe_fd);
	pid = fork();
	//dup_pipe[0] = dup(pipe_fd[0]);
	//dup_pipe[1] = dup(pipe_fd[1]);
	if (pid == 0)
	{
		ft_pipe_in(params, envp, pipe_fd[0], pipe_fd[1]);
		params = params->next;
	}
	waitpid(pid, 0, 0);
	if (pid != 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		dup2(params->fd_stdout, STDOUT);
	}
	//ft_pipe_out(params, envp, pipe_fd[0], pipe_fd[1]);
	return (params);
}