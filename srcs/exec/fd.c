/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:16:28 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/17 20:17:18 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	save_in_out(t_parsing *params)
{
	params->fd_stdin = dup(STDIN);
	params->fd_stdout = dup(STDOUT);
}

void	set_fd(t_parsing *params, int fd)
{
	if (params->file->ftype == 2 || params->file->ftype == 3)
		dup2(fd, 1);
	if (params->file->ftype == 1)
		dup2(fd, 0);
}