/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:48:02 by ddecourt          #+#    #+#             */
/*   Updated: 2021/11/11 00:43:40 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(int fd, char** envp)
{
	int		i;
	char	*path;

	i = -1;
	while (envp[++i])
		if (ft_strnstr(envp[i], "PWD", 3) != 0)
			path = ft_strnstr(envp[i], "PWD", 3);
	i = 3;
	while(path[++i])
		write(fd, &path[i], 1);
	write(fd, "\n", 1);
	free(path);
	return (0);
}