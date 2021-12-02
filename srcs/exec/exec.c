/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:03:55 by ddecourt          #+#    #+#             */
/*   Updated: 2021/12/02 10:07:54 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_process(char **cmd, char *path, char **envp)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		execve(path, cmd, envp);
	else
		waitpid(pid, 0, 0);
	return (0);
}

void	ft_exec(t_parsing *params, char **envp)
{
	char	*right_path;

	if (is_built_in(params, params->tabs[0], envp))
		return ;
	else
	{
		right_path = get_right_path(params, envp);
		if (right_path != NULL)
			exec_process(params->tabs, right_path, envp);
	}
}

int	ft_exec_all_cmd(t_parsing *params, char **envp)
{
	int			fd;
	t_parsing	*tmp;

	fd = 0;
	tmp = params;
	while (params != NULL)
	{
		if (params->type != 0)
			params = ft_exec_redir(params, envp);
		else
		{
			if (params->tabs)
				ft_exec(params, envp);
			params = params->next;
		}
	}
	ft_free_params(tmp);
	return (0);
}
