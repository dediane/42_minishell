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

/*char *ft_get_home(char **envp)
{
	int i;
	char *ret_ptr;
	char *path;

	i = -1;
	get_path(envp, "HOME");
	return (NULL);
}*/

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

/*int	ft_cd(char **envp, char *path)
{
	if (!path)
		return(1);
	if ()
}*/