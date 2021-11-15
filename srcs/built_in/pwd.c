/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:48:02 by ddecourt          #+#    #+#             */
/*   Updated: 2021/11/12 17:06:03 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(int fd, char** envp)
{
	int		i;
	char	*ret_ptr;
	char	*path;

	i = -1;
		i = -1;
	while (envp[++i])
	{
		ret_ptr = ft_strnstr(envp[i], "PWD", 3);
		if (ret_ptr != 0)
			path = ft_strjoin(ret_ptr, "\n");
	}
	i = 3;
	while(path[++i])
		write(fd, &path[i], 1);
	return (0);
}