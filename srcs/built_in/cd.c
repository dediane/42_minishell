/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 00:14:45 by ddecourt          #+#    #+#             */
/*   Updated: 2021/12/09 17:27:31 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *ft_get_home(char **envp)
{
	char *path;
	int i;

	i = -1;
	path = get_path(envp, "HOME", &i);
	if (path == NULL)
		return (NULL);
	return (path);
}

char	*get_path(char **envp, char *to_find, int *i)
{
	int size;
	char *ret_ptr;
	char *path;

	size = ft_strlen(to_find);
	while (envp[++(*i)])
	{
		ret_ptr = ft_strnstr(envp[*i], to_find , size);
		if (ret_ptr != 0)
		{
			// path = ft_strjoin(ret_ptr + (size + 1), "\n");
			path = ft_strdup(ret_ptr + (size + 1));
			//free(ret_ptr);
			return (path);
		}
	}
	return (NULL);
}

int	change_env(char **envp, char *path, char *new_path)
{
	int i;
	char *ret_ptr;

	i = -1;
	ret_ptr = get_path(envp, path, &i);
	//printf("before changes -> %s\n", envp[i]);
	envp[i] = ft_substr(envp[i], 0, ft_strlen(path) + 1);
	envp[i] = ft_strjoin(envp[i], new_path);
	//printf("after changes -> %s\n", envp[i]);
	return (0);
}

int	ft_cd(char **envp, char *path)
{
	char buffer[4096];
	int i;
	
	i = -1;
	if (path == NULL)
	{
		path = ft_get_home(envp);
		//printf("path = %s\n", path);
		//change_env(envp, "OLDPWD", getcwd(buffer, 4096));
		//change_env(envp, "PWD", path);
		//return(0);
	}
	if (ft_strncmp(path, "-", 1) == 0)
	{
		//printf("I am here\n");
		path = get_path(envp, "OLDPWD", &i);
		return(ft_cd(envp, path));
		/*printf("%s\n", path);
		if (chdir(path) == -1)
			return(perror(path), 2);*/
		//return (0);
		//change_env(envp, "OLDPWD", getcwd(buffer, 4096));
		//change_env(envp, "PWD", path);
	}
	else 
	{
		//printf("I am here 2\n");
		change_env(envp, "OLDPWD", getcwd(buffer, 4096));
		//printf("path = [%s]\n", path);
		if (chdir(path) == -1)
			return(perror(path), 2);
		change_env(envp, "PWD", getcwd(buffer, 4096));
		return (0);
	}
}