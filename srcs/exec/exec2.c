/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 00:53:11 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/18 01:00:56 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_pipe_built(t_parsing *params, int pid)
{
	is_built_in(params);
	if (params->next || (params->next && params->next->pipe))
		pipe(params->pipe_fd);
	if (!(params->is_built_in) || (params->pipe || (params->next \
	&& params->next->pipe)))
	{
		params->fork = 1;
		pid = fork();
	}
	return (pid);
}

char	*look_for_relative_path(t_parsing *params, char **envp)
{
	char	*right_path;

	right_path = ft_get_home(envp);
	right_path = ft_strjoin(right_path, "/");
	right_path = ft_strjoin(right_path, params->tabs[0]);
	return (right_path);
}
