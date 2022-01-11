/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:17:26 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/11 22:35:19 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Je récupère mon tableau de paths vers les commandes -> usr/bin etc...
char	**get_cmd_path(char **envp)
{
	int		i;
	int		j;
	char	*path;
	char	**tmp;

	i = -1;
	j = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH", 4) != 0)
			path = ft_strnstr(envp[i], "PATH", 4);
	}
	if (path == NULL)
		return (NULL);
	tmp = ft_split(path + 5, ':');
	return (tmp);
}

// Je checke tous les paths pour trouver le bon et je retourne le bon path
char	*get_right_path(t_parsing *params, char **envp)
{
	char	*path;
	char	*tmp;
	char	**path_array;
	int		i;

	i = -1;
	path_array = get_cmd_path(envp);
	if (path_array != NULL)
	{
		while (path_array[++i])
		{
			tmp = ft_strjoin(path_array[i], "/");
			path = ft_strjoin(tmp, params->tabs[0]);
			free (tmp);
			if (access(path, F_OK) == 0)
			{
				free_tabs(path_array);
				return (path);
			}
			else
				free(path);
		}
	}
	free_tabs(path_array);
	ft_putstr_fd(params->tabs[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	g_exit_value = 127;
	return (NULL);
}

int	open_file(t_parsing *params, char *file)
{
	int	fd;

	if (params->type == 1)
		fd = open(file, O_RDONLY);
	if (params->type == 2)
		fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0664);
	if (params->type == 3)
		fd = open(file, O_RDWR | O_APPEND | O_CREAT, 0664);
	if (params->type == 4)
		fd = ft_heredoc(file, params);
	if (fd < 0)
	{
		g_exit_value = 1;
		ft_putstr("minishell: ");
		return (perror(file), -1);
	}
	return (fd);
}

void	ft_free_params(t_parsing *params)
{
	while (params->next)
	{
		if (params->file)
			ft_free_file(params->file);
		if (params->tabs)
			free_tabs(params->tabs);
		free(params);
		params = params->next;
	}
}

void	ft_free_file(t_file *file)
{
	while (file->next)
	{
		free(file->name);
		free(file);
		file = file->next;
	}
}
