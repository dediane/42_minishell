/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:48:38 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/21 10:51:40 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_nb_files(t_parsing *params, int nb)
{
	while (params->file->next && params->file->next->ftype == 4)
	{
		params->file = params->file->next;
		nb++;
	}
	nb++;
	return (nb);
}
