/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quote_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 20:14:21 by balkis            #+#    #+#             */
/*   Updated: 2022/01/21 14:15:48 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_simple_quote(char *line, int *i, char *argv, t_parsing *param)
{
	if (line)
	{
		ft_tabs(param, line);
		line = NULL;
	}
	if (!ft_add_simple_quote(param, i, argv, line))
		return (0);
	return (1);
}

void	ft_pass_squote(char *argv, int *i)
{
	if (argv[(*i) + 1] == 34)
		(*i)++;
	else if (argv[(*i) + 1] == ' ')
	{
		(*i)++;
		while (argv[(*i)] == ' ')
			(*i)++;
	}
	else if (argv[(*i)] == 39 && argv[(*i) + 1] && argv[(*i) + 1] != ' ')
		(*i)++;
}

int	pos_dolar(char *line)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
			{
				i++;
				len++;
			}
			return (len);
		}
		i++;
	}
	return (0);
}

char	*ft_copy(char *var, char *line, char *exp, int pos)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = pos_dolar(line);
	while (line[i] && i < (pos - 1))
	{
		var[i] = line[i];
		i++;
	}
	while (exp[j])
	{
		var[i] = exp[j];
		j++;
		i++;
	}
	ft_copy2(line, pos, var, i);
	if (line)
		free(line);
	free(exp);
	return (var);
}

void	ft_copy2(char *line, int pos, char *var, int i)
{
	int	len;

	len = pos_dolar(line);
	if (line[pos + len])
	{
		while (line[pos + len])
		{
			var[i] = line[len + pos];
			i++;
			len++;
		}
	}
	var[i] = '\0';
}
