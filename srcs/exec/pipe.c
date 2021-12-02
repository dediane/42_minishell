/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:10:22 by ddecourt          #+#    #+#             */
/*   Updated: 2021/12/02 21:32:04 by ddecourt         ###   ########.fr       */
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

int	ft_pipe_in(t_parsing *params, char **envp, int pipe_w, int pipe_r)
{
	printf("Goes in IN \n");
	(void)pipe_r;
	(void)pipe_w;
	//dup2(pipe_w, STDOUT);
	//close(STDIN);
	//close(pipe_r);
	//printf("Goes in IN \n");
	ft_exec(params, envp);
	printf("Goes in IN \n");
	return (0);
}

int ft_pipe_out(t_parsing *params, char **envp, int pipe_r, int pipe_w)
{
	printf("Goes in OUT \n");
	(void)pipe_w;
	(void)pipe_r;
	//up2(pipe_r, STDIN);
	ft_exec(params, envp);
	printf("Goes in OUT \n");
	return (0);
}

t_parsing	*ft_pipe(t_parsing *params, char **envp)
{
	int pipe_fd[2];
	int cp_fd_1;
	int cp_fd_0;

	printf("Goes in PIPE \n");
	params->fd_stdin = dup(STDIN);
	params->fd_stdout = dup(STDOUT);
	//ft_exec_pipe(params, envp);
	pipe(pipe_fd);
	cp_fd_0 = dup(pipe_fd[0]);
	cp_fd_1 = dup(pipe_fd[1]);
	ft_pipe_in(params, envp, pipe_fd[1], pipe_fd[0]);
	params = params->next;
	ft_pipe_out(params, envp, pipe_fd[0], pipe_fd[1]);
	//close(params->fd_stdin);
	params = params->next;
	return (params);
}
