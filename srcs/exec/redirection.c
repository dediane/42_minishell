/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 20:24:05 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/19 13:41:44 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//execute redirection simple
t_parsing	*ft_redir(t_parsing *params, char **envp)
{
	int			fd;
	t_parsing	*tmp;

	fd = -1;
	if (params->type != 0)
	{
		fd = open_file(params, params->file->name, envp);
		save_in_out(params);
		if (fd == 0)
			return (NULL);
		set_fd(params, fd);
	}
	if (params->tabs)
		exec_in_redir(params, envp);
	if (params->type != 0 && params->pipe == 0)
	{
		close(fd);
		close_fd(params);
	}
	tmp = params;
	params = params->next;
	ft_free_params(tmp);
	return (params);
}

void	exec_in_redir(t_parsing*params, char **envp)
{
	if (!(params->is_built_in))
		ft_exec(params, envp);
	else
		exec_built_in(params, params->tabs[0], &envp);
}

//check le nombre de file et le retourne
int	get_nb_files(t_file *file)
{
	int	i;

	i = 0;
	while (file != NULL)
	{
		file = file->next;
		i++;
	}
	return (i);
}

//execute quand plusieurs redirections
int	ft_multiple_redir(int nb, t_file *file, t_parsing *params, char **envp)
{
	int	fd;

	fd = -1;
	save_in_out(params);
	while (nb > 0)
	{
		fd = open_file(params, file->name, envp);
		if (fd == 0)
			return (0);
		if (nb == 1)
		{
			set_fd(params, fd);
			if (!(params->is_built_in) && nb == 1)
				ft_exec(params, envp);
			else
				exec_built_in(params, params->tabs[0], &envp);
		}
		nb--;
		close(fd);
		file = file->next;
	}
	if (params->heredoc == 1)
		dup2(params->fd_stdin, STDIN);
	close_fd(params);
	return (0);
}

//check si une ou plusieurs redirection
t_parsing	*ft_exec_redir(t_parsing *params, char **envp)
{
	int			i;
	int			ret;
	t_file		*file;

	i = 0;
	file = params->file;
	if (params->file)
		i = get_nb_files(file);
	if (i == 0 || (i != 0 && !params->tabs))
	{
		ft_redir(params, envp);
		if (!params)
			return (NULL);
	}
	if (i != 0 && params->tabs)
	{
		ret = ft_multiple_redir(i, file, params, envp);
		if (ret == 1)
			return (NULL);
	}
	return (params->next);
}
