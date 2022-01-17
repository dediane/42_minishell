/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:03:55 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/17 13:57:06 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//execute une commande: split mon process en 2 process
int	exec_process(char **cmd, char *path, char **envp, t_parsing *params)
{
	int pid;
	
	pid = -1;
	if (params->type != NONE)
	{
		pid = fork();
		if (pid == 0)
			execve(path, cmd, envp);
		else
			waitpid(-1, 0, 0);
	}
	else 
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
		if (params->next || (params->next && params->next->pipe))
			pipe(params->pipe_fd);
		if (!(params->is_built_in) || (params->pipe || (params->next && params->next->pipe)))
		{
			params->fork = 1;
			pid = fork();
		}
		if (pid == 0 || (params->is_built_in && params->fork == 0))
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
			if (params->fork)
				exit(0);
			ft_free_params(head);
			return (envp);
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
	}
	params = head;
	while (params)
	{
		waitpid(-1, &status, 0);//WUNTRACED | WEXITED | WNOHANG);
		if (WIFEXITED(status))
			g_exit_value = WEXITSTATUS(status);
		params = params->next;
	}
	ft_free_params(head);
	return (envp);
}
