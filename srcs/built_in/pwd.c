/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:48:02 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/20 16:11:56 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	wrong_file(char *path)
{
	g_exit_value = 1;
	perror(path);
	free(path);
	return (2);
}

int	wrong_file2(char *s)
{
	printf("minishell: cd: %s not set\n", s);
	g_exit_value = 1;
	return (2);
}

int	check_cd_arg(t_parsing *params)
{
	if (params->tabs[0] && params->tabs[1] && params->tabs[2])
	{
		printf("minishell: cd: too many arguments\n");
		g_exit_value = 1;
		return (0);
	}
	else
		return (1);
}

int	ft_pwd(int fd)
{
	char	buffer[4096];
	size_t	size;

	size = 4096;
	ft_putstr_fd(getcwd(buffer, 4096), fd);
	ft_putchar_fd('\n', fd);
	return (0);
}
