/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:03:50 by bben-yaa          #+#    #+#             */
/*   Updated: 2021/11/09 10:26:31 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	parsing(char *argv, t_parsing *param)
{
	int	i;

	i = 0;
	while(argv[i])
	{
		while(argv[i] == ' ' || argv[i] == '\t')
			i++;
		if (argv[i])
			return (1); ///faire fonction parsing comande///
		return (1); ///print new prompt car on a parser QUE des spaces and tabs///
	}
	return (0); ///argv n'hesite pas -> print new comande
}