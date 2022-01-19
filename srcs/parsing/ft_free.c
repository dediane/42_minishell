/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 16:20:50 by bben-yaa          #+#    #+#             */
/*   Updated: 2022/01/19 10:56:14 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_free_file(t_file *file)
{
	t_file	*tmp;

	while (file)
	{
		tmp = file;
		free(file->name);
		file = file->next;
		free(tmp);
	}
}

void	ft_free_params(t_parsing *params)
{
	t_parsing	*tmp;

	if (params->next)
	{
		free_first_maillon(params);
		params = params->next;
		while (params)
		{
			tmp = params;
			if (params->file)
				ft_free_file(params->file);
			if (params->tabs)
				free_tabs(params->tabs);
			params = params->next;
			free(tmp);
		}
	}
	else
		free_first_maillon(params);
}

void	free_first_maillon(t_parsing *params)
{
	if (params->file)
		ft_free_file(params->file);
	if (params->tabs)
		free_tabs(params->tabs);
}
