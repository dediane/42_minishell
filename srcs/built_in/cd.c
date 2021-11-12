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
	int i;
	char *ret_ptr;
	char *path;

	i = -1;
	while (envp[++i])
	{
		ret_ptr = ft_strnstr(envp[i], "HOME", 4);
		if (ret_ptr != 0)
		{
			path = ft_strjoin(ret_ptr + 5, "\n");
			return (path);
		}
	}
	return (NULL);
}

int	ft_cd(char **envp, char *path)
{
	if (!path)
		
}