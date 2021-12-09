/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:55:05 by ddecourt          #+#    #+#             */
/*   Updated: 2021/12/09 21:54:06 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	export(char *line, char **envp)
{
	int		i;
	int		pos;
	int		size;
	char	*value;

	i = 0;
	size = 0;
	while ((line[i] >= 'a' && line[i] <= 'z') || \
	(line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= '0' && line[i] <= '9'))
		i++;
	if (line[i] != '=')
		return (0);
	pos = i++;
	while (line[i] != '\n')
		i++;
	size = i - pos;
	return (0);
}
