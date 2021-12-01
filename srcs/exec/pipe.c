/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:10:22 by ddecourt          #+#    #+#             */
/*   Updated: 2021/11/29 16:41:08 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pipe(t_parsing *params, int *pipe_fd[2], char **envp)
{
	if (params->pipe == 0 && params->next->pipe != 0)
	{
		printf("ICI\n");
		params->fd_stdin = dup(STDIN);
		params->fd_stdout = dup(STDOUT);
		(void)pipe_fd;
		(void)envp;
		/*pipe(*pipe_fd);
		dup2(*pipe_fd[1], STDOUT);
		//close(pipe_fd[0]);
		ft_exec(params, envp);
		close(params->fd_stdin);
		close(*pipe_fd[1]);
		dup2(params->fd_stdout, STDOUT);*/
		printf("FIN DE FONCTION PIPE\n");
		return (1);
	}
	return (0);
}