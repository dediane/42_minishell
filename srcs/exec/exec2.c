/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 00:53:11 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/19 13:38:43 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_pipe_built(t_parsing *params, int pid)
{
	is_built_in(params);
	if (params->next || (params->next && params->next->pipe))
		pipe(params->pipe_fd);
	if (!(params->is_built_in) || (params->pipe || (params->next \
	&& params->next->pipe)))
	{
		params->fork = 1;
		pid = fork();
	}
	return (pid);
}

//return le vrai path d'un relative path (path du home + path)
char	*look_for_relative_path(t_parsing *params, char **envp)
{
	char	*right_path;

	right_path = ft_get_home(envp);
	right_path = ft_strjoin(right_path, "/");
	right_path = ft_strjoin(right_path, params->tabs[0]);
	return (right_path);
}

void	wait_process(t_parsing *params, int status)
{
	t_parsing	*head;

	head = params;
	while (params)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			g_exit_value = WEXITSTATUS(status);
		params = params->next;
	}
	ft_free_params(head);
}

void	ft_init_exec( int *pid, int *status)
{
	(*pid) = -1;
	(*status) = 0;
}

void	ft_continue(t_parsing *params, t_parsing *head)
{
	ft_launch_signal();
	if (params->fork)
		exit(0);
	ft_free_params(head);
}
