/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:03:55 by ddecourt          #+#    #+#             */
/*   Updated: 2021/11/27 00:54:19 by ddecourt         ###   ########.fr       */
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
	if (ft_strncmp(params->tabs[0], ">", 2) == 0)
		return(fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0664));
	if (ft_strncmp(params->tabs[0], ">>", 3) == 0)
		return(fd = open(file, O_RDWR | O_CREAT, 0664));
	if (ft_strncmp(params->tabs[0], "<", 2) == 0)
		return(fd = open(file, O_RDONLY));
	else
		return(fd = open(file, O_RDONLY));
}

void	ft_exec(t_parsing *params, char **envp)
{
	if (is_built_in(params, params->tabs[0], envp))
		return;
	else 
		exec_process(params->tabs, get_right_path(params, envp), envp);
		//printf("right path = %s\n", get_right_path(params, envp));
}
