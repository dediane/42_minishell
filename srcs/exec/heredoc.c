/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 23:11:44 by ddecourt          #+#    #+#             */
/*   Updated: 2021/12/21 15:23:06 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_eof(char *line, char *eof)
{
	int	size;

	size = ft_strlen(line);
	if (ft_strncmp(eof, line, size) == 0)
		return (1);
	return (0);
}

int	ft_heredoc(char *eof)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line)
		{
			if (check_eof(line, eof))
				break ;
		}
	}
	return (0);
}
