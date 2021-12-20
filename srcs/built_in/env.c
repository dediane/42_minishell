/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:23:58 by ddecourt          #+#    #+#             */
/*   Updated: 2021/12/19 22:16:08 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env(int fd, char **envp)
{
	int	i;
	int	size_line;

	i = -1;
	while (envp[++i])
	{
		size_line = ft_strlen(envp[i]);
		if (size_line)
			write(fd, envp[i], size_line);
		write(fd, "\n", 1);
	}
	return (0);
}
