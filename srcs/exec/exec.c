/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:03:55 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/16 15:35:57 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//execute une commande: split mon process en 2 process
int	exec_process(char **cmd, char *path, char **envp, t_parsing *params)
{
	int	pid;
	(void)pid;
	(void)params;

	//pid = -1;
	//if (params->type != NONE)
	//{
	//	pid = fork();
	//	if (pid == 0)

		execve(path, cmd, envp);
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
	if (exec_built_in(params, params->tabs[0], &envp))
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
			g_exit_value = exec_process(params->tabs, right_path, envp, params);
		free(right_path);
		return (envp);
	}
	return (envp);
}

char	**ft_exec_all_cmd(t_parsing *params, char **envp)
{
	int			fd;
	int			pid;
	int			status;
	t_parsing	*prev;
	t_parsing	*head;

	fd = 0;
	pid = -1;
	prev = NULL;
	head = params;
	while (params != NULL)
	{
		is_built_in(params);
		if (params->next) //!= NULL && params->next->pipe)
			pipe(params->pipe_fd);
		if (!(params->is_built_in)) //|| ((is_built_in(params, params->tabs[0], &envp)) && (params->next->pipe != 0)))
		{
			pid = fork();
			params->fork = 1;
		}
		if (pid == 0 || (params->is_built_in))
		{
			if (params->pipe)
				dup2(prev->pipe_fd[0], 0);
			if (params->next != NULL && params->next->pipe != 0)
				dup2(params->pipe_fd[1], 1);
			ft_disable(pid);
			if (params->file)
				ft_exec_redir(params, envp);
			else
				envp = ft_exec(params, envp);
			ft_launch_signal();		
			//if (params->is_built_in)
			return (envp);
			exit(0);
			//else
		}
		else
		{
			if (prev && prev->pipe)
				close(prev->pipe_fd[0]);
			if (params->next != NULL && params->next->pipe != 0)
				close(params->pipe_fd[1]);
			if (params->pipe && params->next == NULL)
			{
				if (params->pipe_fd[0] != 0)
					close(params->pipe_fd[0]);
			}
		}
		prev = params;
		params = params->next;
		waitpid(-1, &status, 0);//WUNTRACED | WEXITED | WNOHANG);
		if (WIFEXITED(status))
			g_exit_value = WEXITSTATUS(status);
	}
	ft_free_params(head);
	return (envp);
}
