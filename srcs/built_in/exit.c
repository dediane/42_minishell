/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 13:50:59 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/16 23:07:40 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_exit_mess(void)
{
	ft_putstr_fd("exit\n", 2);
	exit(0);
}


int	ft_num(char *s)
{
	int i;
	int flag;

	i = 0;
	flag = ft_strlen(s);
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

void	ft_exit(t_parsing *params)
{
	if (params == NULL)
		ft_exit_mess();
	if (params->tabs[0] && params->tabs[1] && params->tabs[2])
	{
		ft_putstr_fd("exit\nminishell: exit: too many argument\n", 2);
		g_exit_value = 1;
		return ;
	}
	else if (params->tabs[1])
	{
		if (ft_num(params->tabs[1]))
			exit(ft_atoi(params->tabs[1]));
		else
		{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(params->tabs[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(2);
		}
	}
	else
		exit(0);
	return ;
}