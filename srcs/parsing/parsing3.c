/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:42:22 by bben-yaa          #+#    #+#             */
/*   Updated: 2022/01/17 15:01:37 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_heredoc(t_parsing *params, char **env)
{
	t_parsing   *tmp;

	tmp = params;
	while (tmp)
	{
		if (tmp->calldoc)
		{
			printf("calllll heredocs\n");
			ft_heredoc(params->file->name, params, env);
		}
		tmp = tmp->next;
	}
	return (1);
}