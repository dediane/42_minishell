/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 00:47:40 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/20 19:14:38 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_n(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] == '-' && arg[i + 1] && arg[i + 1] == 'n')
	{
		i++;
		while (arg[i] == 'n')
			i++;
		if (arg[i] != 'n' && arg[i])
			return (1);
		return (0);
	}
	return (1);
}

int	check_size(int size, int fd, char **tabs)
{
	while (tabs[size])
		size++;
	if (size == 1)
	{
		ft_putchar_fd('\n', fd);
		return (0);
	}
	return (1);
}

void	ft_write(int fd, t_parsing *params, int *i, int *space)
{
	if (params->tabs[(*i)])
	{
		if (*space)
			ft_putchar_fd(' ', fd);
		*space = 1;
	}
	ft_putstr_fd(params->tabs[(*i)++], fd);
}

void	ft_plus(int *i, int *size)
{
	(*size)++;
	(*i)++;
}

int	ft_echo(int fd, t_parsing *params, int space)
{
	int	size;
	int	n;
	int	i;

	size = 0;
	i = 1;
	n = 1;
	if (!check_size(0, fd, params->tabs))
		return (0);
	while (params->tabs[i] && params->tabs[i][0] == '-')
	{
		n = check_n(params->tabs[i]);
		if (n == 0)
			ft_plus(&i, &size);
		else
			break ;
	}
	while (params->tabs[i])
		ft_write(fd, params, &i, &space);
	if (n == 1 && size == 0)
		ft_putchar_fd('\n', fd);
	g_exit_value = 0;
	return (0);
}
