/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 00:14:45 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/19 20:18:54 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_get_home(char **envp)
{
	char	*path;
	int		i;

	i = -1;
	path = get_path(envp, "HOME", &i);
	if (path == NULL)
		return (NULL);
	return (path);
}

char	*get_path(char **envp, char *to_find, int *i)
{
	int		size;
	char	*ret_ptr;
	char	*path;

	size = ft_strlen(to_find);
	while (envp[++(*i)])
	{
		ret_ptr = ft_strnstr(envp[*i], to_find, size);
		if (ret_ptr != 0)
		{
			path = ft_strdup(ret_ptr + (size + 1));
			return (path);
		}
	}
	return (NULL);
}

int	change_env(char **envp, char *path, char *new_path)
{
	int		i;
	char	*ret_ptr;
	char	*tmp;

	i = -1;
	ret_ptr = get_path(envp, path, &i);
	tmp = ft_substr(envp[i], 0, ft_strlen(path) + 1);
	free(envp[i]);
	envp[i] = ft_strjoin(tmp, new_path);
	free(ret_ptr);
	free(tmp);
	return (0);
}

int	ft_cd(char **envp, char *path, t_parsing *params)
{
	char	buffer[4096];
	int		i;

	i = -1;
	if (path == NULL)
	{
		path = ft_get_home(envp);
		if (!path)
			return (wrong_file2());
	}
	if (ft_strncmp(path, "-", 1) == 0)
	{
		free(path);
		path = get_path(envp, "OLDPWD", &i);
		printf("%s\n", path);
		return (ft_cd(envp, path, params));
	}
	else
	{
		change_env(envp, "OLDPWD", getcwd(buffer, 4096));
		if (chdir(path) == -1)
			return (wrong_file(path));
		change_env(envp, "PWD", getcwd(buffer, 4096));
		free(path);
		return (0);
	}
}
