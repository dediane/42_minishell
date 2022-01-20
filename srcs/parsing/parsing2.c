/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 08:01:08 by balkis            #+#    #+#             */
/*   Updated: 2022/01/20 16:37:15 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_mredoc(char *line, int *i, char *argv, t_parsing *tmp)
{
	if (!ft_check_redoc(argv, (*i)))
	{
		printf("Minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	if (line)
	{
		ft_tabs(tmp, line);
		line = NULL;
	}
	ft_define_redicretcion(argv, i, tmp);
	ft_add_file(tmp, i, argv, line);
	if (!tmp->file)
		return (0);
	while (argv[(*i)] == ' ')
		(*i)++;
	return (1);
}

char	*ft_mdolar(char *argv, int *i, char *line, t_parsing *param)
{
	if (line)
	{
		ft_tabs(param, line);
		line = NULL;
	}
	while (argv[(*i)] && argv[(*i)] != ' ')
	{
		line = ft_line(line, argv[(*i)]);
		(*i)++;
	}
	return (line);
}

char	*ft_mdolar2(char *argv, int *i, char *line, char **envp)
{
	line = find_var(envp, line);
	if (argv[(*i)])
	{
		while (argv[(*i)] == ' ')
			(*i)++;
	}
	return (line);
}

int	ft_mpipe(char *argv, int *i, t_parsing *tmp, t_parsing *param)
{
	ft_add_maillon(param);
	tmp->next->pipe = tmp->pipe + 1;
	(*i)++;
	while (argv[(*i)] && argv[(*i)] == ' ')
		(*i)++;
	if (!argv[(*i)])
		tmp->calldoc = 1;
	if (argv[(*i)] == '|')
		(*i)++;
	if (argv[(*i)] && argv[(*i)] == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 2);
		return (0);
	}
	while (argv[(*i)] && argv[(*i)] == ' ')
		(*i)++;
	if (!argv[(*i)])
		tmp->calldoc = 1;
	return (1);
}

void	ft_mspace(char *argv, int *i, t_parsing *tmp, char *line)
{
	if (argv[(*i)])
	{
		while (argv[(*i)] == ' ')
			(*i)++;
	}
	if (line)
		ft_tabs(tmp, line);
}
