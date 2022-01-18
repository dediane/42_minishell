/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:42:22 by bben-yaa          #+#    #+#             */
/*   Updated: 2022/01/18 08:57:37 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_heredoc(t_parsing *params, char **env)
{
	t_parsing	*tmp;

	tmp = params;
	while (tmp)
	{
		if (tmp->calldoc)
		{
			printf("calllll heredocs\n");
			ft_heredoc(params->file->name, params, env);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	ft_fill(char *argv, int *i, char *buf, char *line)
{
	if (!argv[(*i)])
		return (0);
	buf[0] = argv[(*i)];
	buf[1] = '\0';
	(void)line;
	(*i)++;
	return (1);
}

void	ft_fill2(char *argv, char *line, t_parsing *tmp, int *i)
{
	if (!argv[(*i)] && line)
		ft_tabs(tmp, line);
}

void	mdquote2(char *line, char **envp, t_parsing *param)
{
	if (dolar_quotes(line))
		line = ft_replace_var(line, envp);
	ft_tabs(param, line);
}

int	mdquote3(char *argv, int *i)
{
	if (argv[(*i) + 1] == '\0')
		return (0);
	ft_pass_dquote(argv, i);
	return (1);
}
