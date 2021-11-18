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

	path = get_path(envp, "HOME");
	if (path == NULL)
		return (NULL);
	return (path);
}

char	*get_path(char **envp, char *to_find)
{
	int i;
	int size;
	char *ret_ptr;
	char *path;

	i = -1;
	size = ft_strlen(to_find);
	while (envp[++i])
	{
		ret_ptr = ft_strnstr(envp[i], to_find , size);
		if (ret_ptr != 0)
		{
			path = ft_strjoin(ret_ptr + (size + 1), "\n");
			return (path);
		}
	}
	return (NULL);
}

int	change_env(char **envp)
{
	int i;
	int j;

	i = -1;
	while (envp[i][0] != NULL)
	{
		if ()
	}
}

int	ft_cd(char **envp, char *path)
{
	//if (ft_strncmp(path, "cd", 3) == 0)
	char *home;
	(void)path;
	home = ft_get_home(envp);
	printf("%s\n", home);
	chdir(home);
	return (0);
}