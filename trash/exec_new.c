/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 21:34:45 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/12 23:06:58 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//cherche le lien complet d'un relative path
char	*look_for_relative_path(t_parsing *params, char **envp)
{
	char	*right_path;

	right_path = ft_get_home(envp);
	right_path = ft_strjoin(right_path, "/");
	right_path = ft_strjoin(right_path, params->tabs[0]);
	return (right_path);
}


int	exec_bin(t_parsing *params, t_parsing *prev, char **env)
{
	int		pid;
	char	*right_path;
	(void)	prev;
	
	pid = fork();
	puts("HERE 2");
	//params->fd_stdin = dup(STDIN);
	//params->fd_stdout = dup(STDOUT);
	if (pid == 0)
	{
			right_path = get_right_path(params, env);
			if (!right_path)
				right_path = look_for_relative_path(params, env);
			if (!right_path)
				ft_command_not_found(NULL, params->tabs[0]);
			puts("HERE BEFORE EXECVE");
			execve(*params->tabs, &right_path, env);
	}
	else
	{	
		waitpid(-1, 0, 0);
		/*if (prev && prev->pipe)
		{
			close(prev->pipe_fd[0]);
			ft_free_params(prev);
		}
		if (params->next != NULL && params->next->pipe != 0)
			close(params->pipe_fd[1]);
		if (params->pipe && params->next == NULL)
			close(params->pipe_fd[0]);*/
	}
	return (0);
}

//cherche si redirection
//cherche si pipe

int	get_nb_files(t_file *file)
{
	int	i;

	i = 0;
	while (file != NULL)
	{
		file = file->next;
		i++;
	}
	return (i);
}

//
char	**choose_exec(t_parsing *params, char **env)
{
	t_parsing	*prev;
	//int			nb_file;
	
	prev = NULL;
	/*if (params->file)
	{
		//nb_file = get_nb_files(params->file)
		if (params->type == 1 || params->type == 4)
			dup2(open_file(params, params->file->name), STDIN);
		if (params->type == 2 || params->type == 3)
			dup2(open_file(params, params->file->name), STDOUT);
	}*/
	/*if (params->next && params->next->pipe)
	{
		pipe(params->pipe_fd);
		if (params->pipe)
			dup2(prev->pipe_fd[0], 0);
		if (params->next != NULL && params->next->pipe != 0)
			dup2(params->pipe_fd[1], 1);
	}*/
	if (is_built_in(params, params->tabs[0]))
	{
		env = exec_built_in(params, &env, is_built_in(params, params->tabs[0]));
		/*if (params->file)
		{
			close(params->fd_stdin);
			dup2(params->fd_stdout, STDOUT);
		}*/
		// if (params->pipe)
		// {
			
		// }
	}
	else
	{
		exec_bin(params, prev, env);
	}
	return (env);
}

//boucle primaire
char	**exec_shell(t_parsing *params, char **env)
{
	//int status;
	
	while (params != NULL)
	{
		save_fd(params);
		choose_exec(params, env);
		params = params->next;
		//waitpid(-1, &status, 0);
		puts("SORTIE");
		//if (WIFEXITED(status))
		//	g_exit_value = WEXITSTATUS(status);
	}
	return (env);
}

/*

> <




|




fork

*/