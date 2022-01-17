/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:42:22 by bben-yaa          #+#    #+#             */
/*   Updated: 2022/01/17 13:20:27 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_heredoc(t_parsing *params)
{
	t_parsing   *tmp;

	tmp = params;
	while (tmp)
	{
		if (tmp->calldoc)
		{
			printf("calllll heredocs\n");
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}