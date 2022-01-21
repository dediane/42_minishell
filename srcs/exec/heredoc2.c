/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:48:38 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/21 12:00:57 by ddecourt         ###   ########.fr       */
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

int	ft_break(t_file *file, int eof, int nb, t_file *head)
{
	if (eof == nb)
	{
		file = head;
		return (1);
	}
	return (0);
}

void	ft_print_heredoc(int pipe_fd[2], char *line, int eof, int nb)
{
	if (eof == nb -1)
		print_heredoc(pipe_fd, line);
	return ;
}
