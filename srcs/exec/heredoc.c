/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 23:11:44 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/21 12:12:14 by ddecourt         ###   ########.fr       */
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

char	*ft_value(char *line, char **env)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = ft_strlen(line);
	size--;
	while (env[i])
	{
		if (ft_strncmp(&line[1], env[i], size) == 0)
		{
			if (env[i][size] && env[i][size] == '=' && env[i][size + 1])
				return (&env[i][size + 1]);
		}
		i++;
	}
	return (" ");
}

int	check_eof_multi(t_parsing *params, char *line)
{
	int	size;

	size = ft_strlen(line);
	if (size != 0 && ft_strncmp(line, params->file->name, size) == 0)
	{
		params->file = params->file->next;
		return (1);
	}
	return (0);
}

int	ft_heredoc_multiple(int nb, t_parsing *params, int tmp_stdout)
{
	t_file		*head;
	char		*line;
	int			pipe_fd[2];
	int			eof;

	head = params->file;
	eof = 0;
	if (pipe(pipe_fd))
		return (1);
	nb = ft_nb_files(params->file, nb);
	params->file = head;
	while (1)
	{
		line = readline("> ");
		if (line)
		{
			eof += check_eof_multi(params, line);
			if (ft_break(params->file, eof, nb, head))
				break ;
			ft_print_heredoc(pipe_fd, line, eof, nb);
			free(line);
		}
	}
	close_heredoc(pipe_fd, params, line);
	return (tmp_stdout);
}

int	ft_heredoc(char *eof, t_parsing *params, char **env)
{
	char	*line;
	int		pipe_fd[2];
	int		tmp_stdout;

	tmp_stdout = dup(STDOUT);
	if (pipe(pipe_fd))
		return (1);
	if (params->file->next == NULL)
	{
		while (1)
		{
			line = readline("> ");
			if (line && check_eof(line, eof))
				break ;
			if (line && line[0] == '$')
				line = ft_value(line, env);
			print_heredoc(pipe_fd, line);
			free (line);
		}
		close_heredoc(pipe_fd, params, line);
	}
	else
		tmp_stdout = ft_heredoc_multiple(0, params, tmp_stdout);
	return (tmp_stdout);
}
