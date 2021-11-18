/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 00:14:45 by ddecourt          #+#    #+#             */
/*   Updated: 2021/11/11 15:11:42 by ddecourt         ###   ########.fr       */
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
			path = ft_strjoin(ret_ptr + (size + 1), "\n");
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
	printf("before changes -> %s\n", envp[i]);
	envp[i] = ft_substr(envp[i], 0, ft_strlen(path) + 1);
	envp[i] = ft_strjoin(envp[i], new_path);
	printf("after changes -> %s\n", envp[i]);
	return (0);
}

int	ft_cd(char **envp, char *path)
{
	//if (ft_strncmp(path, "cd", 3) == 0)
	char *home;
	char buffer[4096];
	(void)path;
	home = ft_get_home(envp);
	change_env(envp, "OLDPWD", getcwd(buffer, 4096));
	change_env(envp, "PWD", home);
	//chdir(home);
	return (0);
}