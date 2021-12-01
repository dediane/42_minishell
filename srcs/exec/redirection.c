/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 20:24:05 by ddecourt          #+#    #+#             */
/*   Updated: 2021/12/01 20:57:05 by ddecourt         ###   ########.fr       */
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
	while (params->file->next)
	{
		ft_redir2(params, envp, fd);
		params->file = params->file->next;
	}
	if (params->type != 0 && params->file->next->ftype == 0 && params->pipe == 0)
	{
		close(fd);
		close(params->fd_stdin);
		dup2(params->fd_stdout, STDOUT);
	}
	params = params->next;
	return(params);
}

t_parsing	*ft_redir2(t_parsing *params, char **envp, int fd)
{	
	if (params->type != 0)
	{
		
	}
}