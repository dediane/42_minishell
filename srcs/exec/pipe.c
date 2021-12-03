/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:10:22 by ddecourt          #+#    #+#             */
/*   Updated: 2021/12/03 09:06:37 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*int	ft_exec_pipe(t_parsing *params, char **envp)
{
	char *right_path;
	int pid;
	int pipe_fd[2];
	
	pipe(pipe_fd);
	right_path = get_right_path(params, envp);
		if (right_path != NULL)
		{
			pid = fork();
			if (pid == 0)
			{
				close(pipe_fd[0]);
				execve(*params->tabs, &right_path, envp);
			}
			else
			{
				waitpid(pid, 0, 0);
				close(pipe_fd[1]);
			}
			printf("before exit\n");
			return (0);
		}
	return (1);
}*/

int	ft_pipe_in(t_parsing *params, char **envp, int pipe_out, int pipe_in)
{
	printf("IN - in\n");
	close(pipe_out);
	dup2(pipe_in, STDOUT);
	ft_exec(params, envp);
	close(pipe_in);
	dup2(params->fd_stdout, STDOUT);
	printf("IN - out\n");
	return (0);
}

int ft_pipe_out(t_parsing *params, char **envp, int pipe_out, int pipe_in)
{
	printf("OUT - in\n");
	close(pipe_in);
	dup2(pipe_out, STDIN);
	ft_exec(params, envp);
	close(pipe_out);
	dup2(params->fd_stdin, STDIN);
	printf("OUT- out\n");
	return (0);
}

t_parsing	*ft_pipe(t_parsing *params, char **envp)
{
	int pipe_fd[2];
	int dup_pipe[2];
	
	pipe(pipe_fd);
	params->fd_stdin = dup(STDIN);
	params->fd_stdout = dup(STDOUT);
	dup_pipe[0] = dup(pipe_fd[0]);
	dup_pipe[1] = dup(pipe_fd[1]);
	ft_pipe_in(params, envp, pipe_fd[0], pipe_fd[1]);
	params = params->next;
	ft_pipe_out(params, envp, dup_pipe[0], dup_pipe[1]);
	return (params);
}
