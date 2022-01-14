/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:11:42 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/14 17:37:19 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*int	is_built_in(t_parsing *params)
{
	if (ft_strncmp(params->tabs[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(params->tabs[0], "pwd", 4) == 0)
		return (2);
	else if (ft_strncmp(params->tabs[0], "echo", 5) == 0)
		return (3);
	else if (ft_strncmp(params->tabs[0], "env", 4) == 0)
		return (4);
	else if (ft_strncmp(params->tabs[0], "export", 7) == 0)
		return (5);
	else if (ft_strncmp(params->tabs[0], "unset", 6) == 0)
		return (6);
	return (0);
}

int		exec_built_in(t_parsing *params, char ***envp, int value)
{
	if (value == 1)
	{
		if (!(params->tabs[1]))
			ft_cd(*envp, NULL, params);
		else
			ft_cd(*envp, params->tabs[1], params);
	}
	else if (value == 2)
		ft_pwd(STDOUT);
	else if (value == 3)
		ft_echo(1, params);
	else if (value == 4)
		ft_env(1, *envp);
	else if (value == 5)
		*envp = ft_export(1, params->tabs, *envp);
	else if (value == 6)
		*envp = ft_unset(1, params->tabs, *envp);
	return (0);
}*/

void	is_built_in(t_parsing * params)
{
	if (ft_strncmp(params->tabs[0], "cd", 3) == 0)
		params->is_built_in = 1;
	else if (ft_strncmp(params->tabs[0], "pwd", 4) == 0)
		params->is_built_in = 1;
	else if (ft_strncmp(params->tabs[0], "echo", 5) == 0)
		params->is_built_in = 1;
	else if (ft_strncmp(params->tabs[0], "env", 4) == 0)
		params->is_built_in = 1;
	else if (ft_strncmp(params->tabs[0], "export", 7) == 0)
		params->is_built_in = 1;
	else if (ft_strncmp(params->tabs[0], "unset", 6) == 0)
		params->is_built_in = 1;
	params->is_built_in = 0;
}


int	exec_built_in(t_parsing *params, char *cmd, char ***envp)
{
	int	fd;

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
		return (1);
	}
	else if (ft_strncmp(cmd, "unset", 6) == 0)
	{
		*envp = ft_unset(1, params->tabs, *envp);
		return (1);
	}
	return (0);
}