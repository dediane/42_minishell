/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:23:58 by ddecourt          #+#    #+#             */
/*   Updated: 2021/11/09 19:49:15 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env(int fd, char **envp)
{
	int i;
	
	i = -1;
	while (envp[++i])
	{
		write(fd, envp[i], ft_strlen(envp[i]));
		write(fd, "\n", 1);
	}
	return (0);
}
