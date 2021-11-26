/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:11:42 by ddecourt          #+#    #+#             */
/*   Updated: 2021/11/26 13:44:25 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_built_in(t_parsing *params, char *line, char **envp)
{
    int fd;

    fd = 0;
	/*if (ft_strncmp(line, "cd", 3) == 0)
	{
		if (params->tabs[1] && check_cd_path(line))
			ft_cd(envp, line);
	}*/
	if (ft_strncmp(line, "pwd", 4) == 0)
		ft_pwd(fd = open_file(params, params->file->name), envp);
	else if (ft_strncmp(params->tabs[0], "echo", 5) == 0)
	{
		printf("ici echo\n");
		ft_echo(1, params->tabs);
	}
	else if (ft_strncmp(line, "env", 4) == 0)
		ft_env(1, envp);
	/*else if (ft_strncmp(&line[0], "export", 7) == 0)
		ft_export()
	else if (ft_strncmp(&line[0], "unset", 6) == 0)
		ft_unset()*/
	return (1);
}