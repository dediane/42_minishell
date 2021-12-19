/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:03:55 by ddecourt          #+#    #+#             */
/*   Updated: 2021/12/19 16:34:50 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_process(char **cmd, char *path, char **envp) //execute une commande: split mon process en 2 process
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(path, cmd, envp);
	}
	else
	{
		waitpid(-1, 0, 0);
	}
	return (0);
}

char	**ft_exec(t_parsing *params, char **envp)
{
	char	*right_path;

	if (is_built_in(params, params->tabs[0], &envp))
	{
		//ft_env(1, envp);
		return (envp);
	}
	else
	{
		right_path = get_right_path(params, envp);
		if (right_path != NULL)
			exec_process(params->tabs, right_path, envp);
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
		{
			//printf("exec 1\n");
			params = ft_pipe(params, envp);
		}
		else if ((params->type != 0 && params->next != NULL && params->next->pipe == 0) \
		|| (params->type != 0 && params->next == NULL))
		{
			//printf("exec 2\n");
			params = ft_exec_redir(params, envp);
		}
		else
		{
			//printf("exec 3\n");
			if (params->tabs)
				envp = ft_exec(params, envp);
			params = params->next;
		}
	}
	//ft_free_params(tmp);
	return (envp);
}
