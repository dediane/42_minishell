/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:03:55 by ddecourt          #+#    #+#             */
/*   Updated: 2021/11/19 11:50:09 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


/*

//Fonction qui execute les commandes, à besoin en parametres:
// 2 fd (in & out)
// le PATH d'environnement sous forme de char **
// la liste des commandes et arguments sous forme de char **
//----------------------------------------------------------------//

int	exec_process(int *pipe, int *fd, char **argv, char **envp)
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
}

void	ft_exec(t_parsing *params, char **envp)
{
	
}

*/