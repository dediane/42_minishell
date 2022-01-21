/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:48:38 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/21 11:05:25 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_nb_files(t_file *file, int nb)
{
	while (file->next && file->next->ftype == 4)
	{
		file = file->next;
		nb++;
	}
	nb++;
	return (nb);
}
