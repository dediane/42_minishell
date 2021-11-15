/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 13:50:59 by ddecourt          #+#    #+#             */
/*   Updated: 2021/11/12 19:06:02 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void ft_exit(char *exit_line)
{
	int size;
	//int flag;
	int i;

	size = ft_strlen(exit_line);
	if (ft_strnstr(exit_line, "exit", 4) && size == 4)
	{
		//fonction pour free tous nos mallocs.
		exit(0);
	}
	if (size > 4)
	{
		if (exit_line[4] == ' ')
		{
			i = -1;
			//while ()
		}
		if (exit_line[4] != ' ')
		{
			//fonction pour free tous nos mallocs.
			ft_putstr_fd(exit_line, 2);
			ft_putstr_fd(": command not found\n", 2);
		}
	}
	return;
}