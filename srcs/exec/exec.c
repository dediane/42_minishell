/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:03:55 by ddecourt          #+#    #+#             */
/*   Updated: 2021/12/22 14:30:18 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//execute une commande: split mon process en 2 process
int	exec_process(char **cmd, char *path, char **envp)
{
	int	pid;

	pid = fork();
	ft_disable(pid);
	if (pid == 0)
	{
		execve(path, cmd, envp);
	}
	else
	{
		waitpid(-1, 0, 0);
	}
	ft_launch_signal();
	return (0);
}

char	*look_for_relative_path(t_parsing *params, char **envp)
{
	char	*right_path;

	right_path = ft_get_home(envp);
	right_path = ft_strjoin(right_path, "/");
	right_path = ft_strjoin(right_path, params->tabs[0]);
	return (right_path);
}

char	**ft_exec(t_parsing *params, char **envp)
{
	char	*right_path;
	int		relative;

	relative = 0;
	if (is_built_in(params, params->tabs[0], &envp))
		return (envp);
	else
	{
		if (access(params->tabs[0], F_OK) == 0)
		{
			relative = 1;
			right_path = ft_strdup(params->tabs[0]);
		}
		if (relative == 0)
			right_path = get_right_path(params, envp);
		else if (!right_path)
			right_path = look_for_relative_path(params, envp);
		if (right_path != NULL)
			params->ret_value = exec_process(params->tabs, right_path, envp);
		return (envp);
	}
	return (envp);
}

char	**ft_exec_all_cmd(t_parsing *params, char **envp)
{
	int			fd;
	t_parsing	*tmp;

	fd = 0;
	tmp = params;
	while (params != NULL)
	{
		if (params->next != NULL && params->next->pipe != 0)
			params = ft_pipe(params, envp);
		else if ((params->type != 0 && params->next != NULL && \
		params->next->pipe == 0) || (params->type != 0 && params->next == NULL))
			params = ft_exec_redir(params, envp);
		else
		{
			if (params->tabs)
				envp = ft_exec(params, envp);
			params = params->next;
		}
	}
	return (envp);
}
