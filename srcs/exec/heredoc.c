/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 23:11:44 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/16 13:18:59 by bben-yaa         ###   ########.fr       */
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

int	ft_heredoc(char *eof, t_parsing *params)
{
	char	*line;
	int		pipe_fd[2];
	int		tmp_stdin;
	int		tmp_stdout;

	tmp_stdin = dup(STDIN);
	tmp_stdout = dup(STDOUT);
	if (pipe(pipe_fd))
		return (1);
	while (1)
	{
		line = readline("> ");
		if (line)
		{
			if (check_eof(line, eof))
				break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
	}
	dup2(pipe_fd[0], STDIN);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	params->heredoc = 1;
	return (tmp_stdout);
}
