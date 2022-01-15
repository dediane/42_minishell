/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 13:50:59 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/15 16:04:51 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_exit_mess(void)
{
	ft_putstr_fd("exit\n", 1);
	exit(0);
}

void	ft_exit(char *exit_line)
{
	int	size;
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	if (exit_line == NULL)
		ft_exit_mess();
	size = ft_strlen(exit_line);
	while ((exit_line[i] > 8 && exit_line[i] < 14) || exit_line[i] == 32)
		i++;
	if (exit_line[i] != 'e')
		flag = 1;
	if (ft_strnstr(exit_line, "exit", ft_strlen(exit_line)) && flag == 0)
		ft_exit_mess();
	if (flag == 1)
	{
		if (exit_line[i] != ' ')
		{
			ft_putstr_fd(exit_line, 2);
			ft_putstr_fd(": command not found\n", 2);
		}
	}
	return ;
}

/*dans if (flag == 1)
			if (exit_line[i] == ' ')
			{
				//while ()
			}
j'ai mis ce commentaire pour la norme je pense pas qu'on s'en servait de base*/