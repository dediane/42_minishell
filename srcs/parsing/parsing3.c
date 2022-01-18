/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:42:22 by bben-yaa          #+#    #+#             */
/*   Updated: 2022/01/18 18:02:28 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

int	s_quote(t_param *arg, t_parsing *tmp)
{
	if (!ft_simple_quote(arg->line, &(arg->i), arg->argv, tmp))
		return (0);
	if (arg->argv[arg->i + 1] == '\0')
		return (-1);
	ft_pass_squote(arg->argv, &(arg->i));
	arg->line = NULL;
	return (3);
}
