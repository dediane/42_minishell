/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:03:55 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/19 20:02:10 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//execute une commande: split mon process en 2 process
int	exec_process(char **cmd, char *path, char **envp, t_parsing *params)
{
	int	pid;

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

//cherche si built-in, sinon cherche path et execute la commande
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

//execute process enfant ou built-in
char	**ft_exec_1(t_parsing *params, t_parsing *prev, char **envp)
{
	if (prev && params->pipe)
	{
		dup2(prev->pipe_fd[0], 0);
		close(prev->pipe_fd[0]);		
	}
	if (params->next != NULL && params->next->pipe != 0)
	{
		dup2(params->pipe_fd[1], 1);
		close(params->pipe_fd[0]);
	}
	if (params->file)
		ft_exec_redir(params, envp);
	else
		envp = ft_exec(params, envp);
	return (envp);
}

//close si pipe ou fork
void	ft_exec_2(t_parsing *params, t_parsing *prev)
{
	if (params->pipe && prev)
		close(prev->pipe_fd[0]);		
	if (prev && prev->pipe)
		close(prev->pipe_fd[1]);
	if (params->next != NULL && params->next->pipe != 0)
		close(params->pipe_fd[1]);
	if (params->pipe && params->next == NULL)
	{
		dup2(params->fd_stdin, STDIN);
		dup2(params->fd_stdout, STDOUT);
		if (params->pipe_fd[1] && params->pipe_fd[1] != 0)
			close(params->pipe_fd[1]);
		if (params->pipe_fd[0] && params->pipe_fd[0] != 0)
			close(params->pipe_fd[0]);
	}
}

//boucle sur chacun des maillons
char	**ft_exec_all_cmd(t_parsing *params, char **envp)
{
	int			pid;
	int			status;
	t_parsing	*prev;
	t_parsing	*head;

	ft_init_exec(&pid, &status);
	prev = NULL;
	head = params;
	while (params != NULL)
	{
		pid = check_pipe_built(params, pid);
		ft_disable(pid);
		if (pid == 0 || (params->is_built_in && params->fork == 0))
		{
			envp = ft_exec_1(params, prev, envp);
			ft_continue(params, head);
			return (envp);
		}
		else
			ft_exec_2(params, prev);
		prev = params;
		params = params->next;
	}
	wait_process(head, status);
	return (envp);
}
