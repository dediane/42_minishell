/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:11:42 by ddecourt          #+#    #+#             */
/*   Updated: 2021/11/26 12:23:47 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_built_in(t_parsing *params, char **line, char **envp)
{
    int fd;

    fd = 0;
	if (ft_strncmp(line[0], "cd", 3) == 0)
	{
		if (line[1] && check_cd_path(line[1]))
			ft_cd(envp, line[1]);
	}
	if (ft_strncmp(line[0], "pwd", 4) == 0)
		ft_pwd(fd = open_file(params, params->file), envp);
	if (ft_strncmp(line[0], "echo", 5) == 0)
		ft_echo(fd = open_file(params, params->tabs[2]), envp);
	if (ft_strncmp(line[0], "env", 4) == 0)
		ft_env(1, envp);
	/*if (ft_strncmp(line[0], "export", 7) == 0)
		ft_export()
	if (ft_strncmp(line[0], "unset", 6) == 0)
		ft_unset()*/
}