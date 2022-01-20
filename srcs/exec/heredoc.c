/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 23:11:44 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/20 18:20:55 by bben-yaa         ###   ########.fr       */
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
	int size;

	i = 0;
	j = 0;
	size = ft_strlen(line);
	size--;
	while(env[i])
	{
		if (ft_strncmp(&line[1], env[i], size) == 0)
		{
			if(env[i][size] && env[i][size] == '=' && env[i][size + 1])
				return (&env[i][size + 1]);
		}
		i++;
	}
	return (" ");
}

int	ft_heredoc(char *eof, t_parsing *params, char **env)
{
	char	*line;
	int		pipe_fd[2];
	int		tmp_stdout;

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
				line = ft_value(line, env);
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
