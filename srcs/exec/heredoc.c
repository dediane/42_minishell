/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 23:11:44 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/17 17:02:39 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_eof(char *line, char *eof)
{
	int	size;

	if (line != NULL)
	{
		size = ft_strlen(line);
		if (size != 0 && ft_strncmp(eof, line, size) == 0)
			return (1);
	}
	return (0);
}

int	ft_heredoc(char *eof, t_parsing *params, char **env)
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
			if (line[0] == '$')
				line = ft_replace_var(line, env);
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
