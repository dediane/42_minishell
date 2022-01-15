/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 18:49:21 by balkis            #+#    #+#             */
/*   Updated: 2022/01/15 14:10:24 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_double_quote(char *line, int *i, char *argv, t_parsing *param)
{
	if (line)
	{
		ft_tabs(param, line);
		line = NULL;
	}
	return (ft_add_double_quote(param, i, argv, line));
}

void	ft_pass_dquote(char *argv, int *i)
{
	if (argv[(*i) + 1] && (argv[(*i) + 1] == 34 || argv[(*i) + 1] == 39))
		(*i)++;
	else if (argv[(*i) + 1] && argv[(*i) + 1] == ' ')
	{
		(*i)++;
		while (argv[(*i)] == ' ')
			(*i)++;
	}
	else if (argv[(*i) + 1] && (argv[(*i) + 1] == '<' || argv[(*i) + 1] == '>'))
		(*i)++;
	else if (argv[(*i)] == 34 && argv[(*i) + 1] && argv[(*i) + 1] != ' ')
		(*i)++;
}

char	*ft_add_double_quote(t_parsing *param, int *i, char *argv, char *line)
{
	(void)param;
	if (!ft_check_quote(&argv[*i], 34))
	{
		printf("les doubles quotes ne sont pas fermées\n");
		param->stop = 1;
		g_exit_value = 1;
		return (0);
	}
	(*i)++;
	while (argv[(*i)] != 34 && argv[(*i)])
	{
		line = ft_line(line, argv[(*i)]);
		(*i)++;
	}
	return (line);
}

int	ft_add_simple_quote(t_parsing *param, int *i, char *argv, char *line)
{
	int	start;

	start = (*i);
	(*i)++;
	while (argv[(*i)] != 39 && argv[(*i)])
	{
		line = ft_line(line, argv[(*i)]);
		(*i)++;
	}
	if (!ft_check_quote(&argv[start], 39))
	{
		free (line);
		printf("les simples quotes ne sont pas fermées\n");
		g_exit_value = 1;
		return (0);
	}
	if (line)
		ft_tabs(param, line);
	return (1);
}

int	ft_check_quote(char *argv, int a)
{
	char	c;
	int		i;
	int		p;

	i = 0;
	c = a;
	p = 0;
	while (argv[i])
	{
		if (i != 0 && argv[i + 1] && argv[i + 1] == c)
		{
			p++;
			break ;
		}
		if (argv[i] == c)
			p++;
		i++;
	}
	if (p % 2)
		return (0);
	else
		return (1);
}
