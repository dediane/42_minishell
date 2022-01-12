/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 22:55:47 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/12 23:03:16 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	save_fd(t_parsing *params)
{
	params->fd_stdin = STDIN;
	params->fd_stdout = STDOUT;
}

void	close_all(t_parsing *params)
{
	close(params->fd_stdin);
	close(params->fd_stdout);
	close(params->pipe_fd[0]);
	close(params->pipe_fd[1]);
}