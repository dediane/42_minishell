/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:03:50 by bben-yaa          #+#    #+#             */
/*   Updated: 2022/01/20 10:40:28 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_init_param(char*argv, char **envp, t_param *arg)
{
	arg->argv = argv;
	arg->i = 0;
	arg->line = NULL;
	arg->envp = envp;
	arg->buf = NULL;
}

int	parsing(char *argv, t_parsing *param, char **envp)
{
	t_param		arg;
	t_parsing	*tmp;
	int			ret;
	int			ret2;

	if (!ft_init(param, &arg, argv, envp))
		return (0);
	tmp = param;
	while (arg.argv[arg.i])
	{
		ret = ft_first_if(param, tmp, &arg);
		if (ret == -1)
			break ;
		else if (ret == 2)
		{
			if (tmp->next)
				tmp = tmp->next;
			ret2 = ft_second_if(&arg, tmp);
			if (ret2 == 3)
				ft_third_if(&arg, tmp);
		}
		if (ret2 == 0 || ret == 0)
			return (0);
	}
	return (1);
}

int	ft_first_if(t_parsing *param, t_parsing *tmp, t_param *arg)
{
	if (arg->argv[arg->i] == 34)
	{
		arg->line = ft_double_quote(arg->line, &(arg->i), arg->argv, tmp);
		if (tmp->stop == 1)
			return (0);
		if (arg->line == 0)
			return (-1);
		mdquote2(arg->line, arg->envp, tmp);
		if (!mdquote3(arg->argv, &(arg->i)))
			return (-1);
		arg->line = NULL;
	}
	else if (arg->argv[arg->i] == 39)
		return (s_quote(arg, tmp));
	else if (arg->argv[arg->i] == '|')
	{
		if (!ft_mpipe(arg->argv, &(arg->i), tmp, param))
			return (0);
	}
	else
		return (2);
	return (3);
}

int	ft_second_if(t_param *arg, t_parsing *tmp)
{
	if ((arg->argv[arg->i] == '<' || arg->argv[arg->i] == '>'))
	{
		if (!ft_mredoc(arg->line, &(arg->i), arg->argv, tmp))
			return (0);
		arg->line = NULL;
	}
	else if ((arg->argv[arg->i] == '$' && arg->argv[arg->i + 1] && \
		arg->argv[arg->i + 1] != '?' && ft_change(&(arg->argv[arg->i]))) \
		|| ft_dolar_v(arg))
	{
		if (ft_dolar_v(arg))
			return (ft_dolar_q(arg, tmp));
		arg->line = ft_mdolar(arg->argv, &(arg->i), arg->line, tmp);
		arg->line = ft_mdolar2(arg->argv, &(arg->i), arg->line, arg->envp);
		ft_tabs(tmp, arg->line);
		arg->line = NULL;
	}
	else if (arg->argv[arg->i] == ' ')
	{
		ft_mspace(arg->argv, &(arg->i), tmp, arg->line);
		arg->line = NULL;
	}
	else
		return (3);
	return (1);
}

void	ft_third_if(t_param *arg, t_parsing *tmp)
{
	arg->buf = malloc(sizeof(char) * 2);
	ft_fill(arg->argv, &(arg->i), arg->buf, arg->line);
	arg->line = ft_line(arg->line, arg->buf[0]);
	if (!arg->argv[arg->i] && arg->line)
		ft_tabs(tmp, arg->line);
	free(arg->buf);
}
