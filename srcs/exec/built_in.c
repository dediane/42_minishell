/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:11:42 by ddecourt          #+#    #+#             */
/*   Updated: 2021/12/20 18:48:35 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_built_in(t_parsing *params, char *cmd, char ***envp)
{
    int fd;

    fd = 0;
	if (ft_strncmp(cmd, "cd", 3) == 0)
	{
		if (!(params->tabs[1]))
			ft_cd(*envp, NULL, params);
		else
			ft_cd(*envp, params->tabs[1], params);
		return (1);
	}
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
	{
		ft_pwd(STDOUT);
		return (1);
	}
	else if (ft_strncmp(params->tabs[0], "echo", 5) == 0)
	{
		ft_echo(1, params);
		return (1);
	}
	else if (ft_strncmp(cmd, "env", 4) == 0)
	{
		ft_env(1, *envp);
		return (1);
	}
	else if (ft_strncmp(cmd, "export", 7) == 0)
	{
		*envp = ft_export(1, params->tabs, *envp);
		//ft_print_tab(*envp);
		return (1);
	}
	else if (ft_strncmp(cmd, "unset", 6) == 0)
	{
		*envp = ft_unset(1, params->tabs, *envp);
		return (1);
	}
	return (0);
}