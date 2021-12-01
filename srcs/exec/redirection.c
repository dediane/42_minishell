/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 20:24:05 by ddecourt          #+#    #+#             */
/*   Updated: 2021/12/01 23:16:00 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_parsing	*ft_redir(t_parsing *params, char **envp)
{
	int fd;

	if (params->type != 0)
	{
		params->fd_stdin = dup(STDIN);
		params->fd_stdout = dup(STDOUT);
		fd = open_file(params, params->file->name);
		dup2(fd, 1);
	}
	if (params->tabs)
		ft_exec(params, envp);
	if (params->type != 0 && params->pipe == 0)
	{
		close(fd);
		close(params->fd_stdin);
		dup2(params->fd_stdout, STDOUT);
	}
	params = params->next;
	return(params);
}

int	get_nb_files(t_file *file)
{
	int i;

	i = 0;
	while(file != NULL)
	{
		file = file->next;
		i++;
	}
	return (i);
}

void	ft_multiple_redir(int nb, t_file *file, t_parsing *params, char **envp)
{
	int fd;

	params->fd_stdin = dup(STDIN);
	params->fd_stdout = dup(STDOUT);
	while (nb > 0)
	{
		fd = open_file(params, file->name);
		dup2(fd, 1);
		ft_exec(params, envp);
		nb--;
		if (nb != 0)
			fd = open(file->name, O_TRUNC);
		close(fd);
		file = file->next;
	}
	close(params->fd_stdin);
	dup2(params->fd_stdout, STDOUT);
}

t_parsing	*ft_exec_redir(t_parsing *params, char **envp)
{
	int i;
	t_file *file;
	
	i = 0;
	file = params->file;
	if (params->file)
		i = get_nb_files(file);
	if (i == 0)
		ft_redir(params, envp);
	else
		ft_multiple_redir(i, file, params, envp);
	return(params->next);
}
