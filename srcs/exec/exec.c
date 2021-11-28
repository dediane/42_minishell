/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:03:55 by ddecourt          #+#    #+#             */
/*   Updated: 2021/11/28 21:00:24 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


/*

//Fonction qui execute les commandes, à besoin en parametres:
// 2 fd (in & out)
// le PATH d'environnement sous forme de char **
// la liste des commandes et arguments sous forme de char **
//----------------------------------------------------------------//*/

/*int	exec_process(int *pipe, int *fd, char **argv, char **envp)
{
	char	**path_array;
	char	**cmd;

	if (*fd == -1)
	{
		perror(argv[1]);
		exit(0);
	}
	dup2(*pipe, STDOUT_FILENO);
	dup2(*fd, STDIN_FILENO);
	path_array = get_path(envp);
	cmd = ft_split(argv[2], ' ');
	if (path_array == NULL)
		exit(1);
	execve(find_path(cmd[0], path_array), cmd, envp);
	free(cmd);
	return (0);
}

//Fonction qui va tester tous les paths disponibles pour trouver la commande:
// en parametres:
//  - un char * avec la commande
//  - le char ** path_array
//----------------------------------------------------------------//

char	*find_path(char *cmd, char **path_array)
{
	char	*path;
	int		i;

	i = -1;
	while (path_array[++i])
	{
		path = ft_strjoin(path_array[i], "/");
		path = ft_strjoin(path, cmd);
		if (access(path, F_OK) == 0)
			return (path);
	}
	ft_clear_tab(&path_array);
	ft_putstr_fd(&cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
	return (NULL);
}*/

int	exec_process(char **cmd, char *path, char **envp)
{
	int pid;

	pid = fork();
	if (pid == 0)
		execve(path, cmd, envp);
	else
		waitpid(pid, 0, 0);
	return (0);
}

char	**get_cmd_path(char **envp)
{
	int		i;
	int		j;
	char	*path;

	i = -1;
	j = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH", 4) != 0)
			path = ft_strnstr(envp[i], "PATH", 4);
	}
	return (ft_split(path + 5, ':'));
}

char *get_right_path(t_parsing *params, char **envp)
{
	char *path;
	char **path_array;
	int i;

	i = 0;
	path_array = get_cmd_path(envp);
	while (path_array[++i])
	{
		path = ft_strjoin(path_array[i], "/");
		path = ft_strjoin(path, params->tabs[0]);
		if (access(path, F_OK) == 0)
			return (path);
	}
	ft_putstr_fd(params->tabs[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	return (NULL);
}

int open_file(t_parsing *params, char *file)
{
	int fd;
	if (params->type == 1 || params->type == 4)
		return(fd = open(file, O_RDONLY));
	if (params->type == 2)
		return(fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0664));
	if (params->type == 3)
		return(fd = open(file, O_RDWR | O_CREAT, 0664));	
	else
		return(0);
}

void	ft_exec(t_parsing *params, char **envp)
{
	char *right_path;

	if (is_built_in(params, params->tabs[0], envp))
		return;
	else 
	{
		right_path = get_right_path(params, envp);
		if (right_path != NULL)
			exec_process(params->tabs, right_path, envp);
		//printf("right path = %s\n", get_right_path(params, envp));
	}
}

int		ft_exec_all_cmd(t_parsing *params, char **envp)
{
	int fd;

	fd = 0;
	while (params->next)
	{
		params->fd_stdin = dup(STDIN);
		params->fd_stdout = dup(STDOUT);
		if (params->type != 0)
			fd = open_file(params, params->file->name);
		dup2(fd, 1);
		ft_exec(params, envp);
		close(fd);
		close(params->fd_stdin);
		dup2(params->fd_stdout, STDOUT);
		if (params->next)
			params = params->next;
	}
	if (params->type != 0)
	{
		params->fd_stdin = dup(STDIN);
		params->fd_stdout = dup(STDOUT);
		fd = open_file(params, params->file->name);
		dup2(fd, 1);
		ft_exec(params, envp);
		close(fd);
		close(params->fd_stdin);
		dup2(params->fd_stdout, STDOUT);
	}
	else
		ft_exec(params, envp);
	return (0);
}
