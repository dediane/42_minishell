/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:11:42 by ddecourt          #+#    #+#             */
/*   Updated: 2021/11/26 18:27:47 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_built_in(t_parsing *params, char *cmd, char **envp)
{
    int fd;

    fd = 0;
	if (ft_strncmp(cmd, "cd", 3) == 0)
	{
		if (!(params->tabs[1]))
			ft_cd(envp, NULL);
		else
			ft_cd(envp, params->tabs[1]);
		return (1);
	}
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
	{
		ft_pwd(STDOUT, envp);
		return (1);
	}
	else if (ft_strncmp(params->tabs[0], "echo", 5) == 0)
	{
		ft_echo(1, params->tabs);
		return (1);
	}
	else if (ft_strncmp(cmd, "env", 4) == 0)
	{
		ft_env(1, envp);
		return (1);
	}
	/*else if (ft_strncmp(cmd, "export", 7) == 0)
		ft_export()
	else if (ft_strncmp(cdm, "unset", 6) == 0)
		ft_unset()*/
	return (0);
}