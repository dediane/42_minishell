/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dolar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 10:40:00 by bben-yaa          #+#    #+#             */
/*   Updated: 2022/01/20 10:42:48 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_dolar_q(t_param *arg, t_parsing *tmp)
{
	char	*number;
	int		i;

	i = -1;
	arg->i += 2;
	number = ft_itoa(g_exit_value);
	if (arg->line)
	{
		ft_tabs(tmp, arg->line);
		arg->line = NULL;
	}
	while (number[++i])
		arg->line = ft_line(arg->line, number[i]);
	ft_tabs(tmp, arg->line);
	arg->line = NULL;
	free(number);
	return (1);
}

int	ft_dolar_v(t_param *arg)
{
	if (arg->argv[arg->i] == '$' && arg->argv[arg->i + 1] && \
		arg->argv[arg->i + 1] == '?' && ((arg->argv[arg->i + 2] \
		&& arg->argv[arg->i + 2] == ' ' ) || !arg->argv[arg->i + 2]))
		return (1);
	else
		return (0);
}
