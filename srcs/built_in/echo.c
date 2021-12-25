/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balkis <balkis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 00:47:40 by ddecourt          #+#    #+#             */
/*   Updated: 2021/12/25 15:42:22 by balkis           ###   ########.fr       */
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

int	ft_echo(int fd, t_parsing *params)
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
		{
			size++;
			i++;
		}
		else
			break ;
	}
	while (params->tabs[i])// && params->tabs[i][0] != '$')
	{
		if (ft_strncmp(params->tabs[i], "$?", 3) == 0)
			ft_putnbr_fd(exit_value, fd);
			//ft_putnbr_fd(params->ret_value, fd);
		else
			ft_putstr_fd(params->tabs[i], fd);
		if (params->tabs[i++])
			ft_putchar_fd(' ', fd);
	}
//	if (params->tabs[i] && params->tabs[i][0] == '$')
//		ft_putnbr_fd(params->ret_value, fd);
	if (n == 1 && size == 0)
		ft_putchar_fd('\n', fd);
	exit_value = 0;
	//params->ret_value = 0;
	return (0);
}
