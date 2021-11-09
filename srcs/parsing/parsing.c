/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:03:50 by bben-yaa          #+#    #+#             */
/*   Updated: 2021/11/09 12:37:12 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	parsing(char *argv)
{
	//t_parsing param;
	int	i;

	i = 0;
	while(argv[i])
	{
		while(argv[i] == ' ' || argv[i] == '\t')
			i++;
		if (argv[i])
			return (1); ///faire fonction parsing comande///
		return (0); ///print new prompt car on a parser QUE des spaces and tabs///
	}
	return (0); ///argv n'hesite pas -> print new comande
}

/////-> si parsing == 0 -> print new prompt
/////-> si parsing == 1 -> executer commande
/////-> si parsing == -1 -> print message "Error" + new prompt

/*int	parsing_comande(char *argv, t_parsing *param, int *i)
{
	
}*/