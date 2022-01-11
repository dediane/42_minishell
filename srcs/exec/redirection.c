/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 20:24:05 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/11 21:38:38 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_parsing	*ft_redir(t_parsing *params, char **envp)
{
	int	fd;

	if (params->type != 0)
	{
		fd = open_file(params, params->file->name);
		if (fd < 0)
			return (NULL);
		//params->fd_stdin = dup(STDIN);
		//params->fd_stdout = dup(STDOUT);
		dup2(fd, 1);
	}
	if (params->tabs)
	{
		ft_exec(params, envp);
	}
	//if (params->type != 0 && params->pipe == 0)
	//{
		//close(fd);
		//close(params->fd_stdin);
		//dup2(params->fd_stdout, STDOUT);
	//}
	//params = params->next;
	return (params);
}

int	get_nb_files(t_file *file)
{
	int	i;

	i = 0;
	while (file != NULL)
	{
		file = file->next;
		i++;
	}
	return (i);
}

int	ft_multiple_redir(int nb, t_file *file, t_parsing *params, char **envp)
{
	int	fd;

	params->fd_stdin = dup(STDIN);
	params->fd_stdout = dup(STDOUT);
	while (nb > 0)
	{
		fd = open_file(params, file->name);
		if (fd < 0)
			return (1);
		dup2(fd, 1);
		ft_exec(params, envp);
		nb--;
		if (nb != 0)
		{
			fd = open(file->name, O_TRUNC);
			if (fd < 0)
				return (1);
		}
		close(fd);
		file = file->next;
	}
	if (params->heredoc == 1)
		dup2(params->fd_stdin, STDIN);
	close(params->fd_stdin);
	dup2(params->fd_stdout, STDOUT);
	return (0);
}

t_parsing	*ft_exec_redir(t_parsing *params, char **envp)
{
	int		i;
	int		ret;
	t_file	*file;

	i = 0;
	file = params->file;
	if (params->file)
		i = get_nb_files(file);
	if (i == 0 || (i != 0 && !params->tabs))
	{
		ft_redir(params, envp);
		if (!params)
			return (NULL);
	}
	if (i != 0 && params->tabs)
	{
		ret = ft_multiple_redir(i, file, params, envp);
		if (ret == 1)
			return (NULL);
	}
	return (params->next);
}
