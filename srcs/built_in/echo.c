/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 00:47:40 by ddecourt          #+#    #+#             */
/*   Updated: 2021/12/16 22:58:55 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_n(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] == '-' && arg[i])
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

int	check_size(int size, int fd, char **arg)
{
	while (arg[size])
		size++;
	if (size == 1)
	{
		ft_putchar_fd('\n', fd);
		return (0);
	}
	return (1);
}

int	ft_echo(int fd, char **arg)
{
	int	size;
	int	n;
	int	i;

	size = 0;
	i = 1;
	n = 1;
	if(!check_size(0, fd, arg))
		return (0);
	while (arg[i] && arg[i][0] == '-')
	{
		n = check_n(arg[i]);
		if (n == 0)
		{
			size++;
			i++;
		}
		else
			break ;
	}
	while (arg[i])
	{
		ft_putstr_fd(arg[i++], fd);
		if (arg[i])
			ft_putchar_fd(' ', fd);
	}
	if (n == 1 && size == 0)
		ft_putchar_fd('\n', fd);
	return (0);
}
