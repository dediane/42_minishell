/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 21:04:33 by balkis            #+#    #+#             */
/*   Updated: 2022/01/19 11:28:58 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	init_parsing(t_parsing *param)
{
	param->nb_cmd = 0;
	param->tabs = NULL;
	param->pipe = 0;
	param->index = 0;
	param->fd_stdin = 0;
	param->fd_stdout = 0;
	param->heredoc = 0;
	param->is_built_in = 0;
	param->fork = 0;
	param->calldoc = 0;
	param->stop = 0;
	param->pipe_fd[0] = 0;
	param->pipe_fd[1] = 0;
	param->type = NONE;
	param->file = NULL;
	param->next = NULL;
	return (1);
}

char	*ft_line(char *line, char buf)
{
	int		i;
	char	*new;

	if (line == NULL)
	{
		new = malloc(sizeof(char) * 2);
		new[0] = buf;
		new[1] = '\0';
		return (new);
	}
	i = ft_strlen(line);
	new = malloc(sizeof(char) * (i + 2));
	i = 0;
	while (line[i])
	{
		new[i] = line[i];
		i++;
	}
	new[i] = buf;
	new[++i] = '\0';
	free(line);
	return (new);
}

char	ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	if (*dest)
		dest[i] = '\0';
	return (*dest);
}

int	ft_init(t_parsing *param, t_param *arg, char *argv, char **envp)
{
	ft_init_param(argv, envp, arg);
	init_parsing(param);
	if (!alloue_elem(param))
		return (0);
	if (!init_parsing(param))
		return (0);
	param->next = NULL;
	arg->i = 0;
	if (!ft_pass_space(argv, &(arg->i)))
		return (0);
	return (1);
}

int	ft_pass_space(char *argv, int *i)
{
	while (argv[(*i)] == ' ' || argv[(*i)] == '\t')
		(*i)++;
	if (!argv[(*i)])
		return (0);
	return (1);
}
