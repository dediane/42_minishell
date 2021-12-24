/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balkis <balkis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 11:37:17 by bben-yaa          #+#    #+#             */
/*   Updated: 2021/12/24 13:01:28 by balkis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	alloue_elem(t_parsing *param)
{
	t_parsing	*new;

	new = (t_parsing *)malloc(sizeof(t_parsing));
	if (!new)
		return (0);
	if (!param)
		param = new;
	return (1);
}

int	ft_add_maillon(t_parsing *param)
{
	t_parsing	*tmp;
	t_parsing	*new;

	tmp = param;
	while (tmp->next)
		tmp = tmp->next;
	new = (t_parsing *)malloc(sizeof(t_parsing));
	if (!new)
		return (0);
	tmp->next = new;
	new->next = NULL;
	new->nb_cmd = 0;
	new->tabs = NULL;
	new->pipe = 0;
	new->index = 0;
	new->ret_value = 0;
	new->heredoc = 0;
	new->stop = 0;
	new->fd_stdout = 0;
	new->fd_stdin = 0;
	new->type = NONE;
	new->file = NULL;
	return (1);
}

void	ft_index(t_parsing *param)
{
	t_parsing	*tmp;
	int			i;

	tmp = param;
	i = 0;
	while (tmp)
	{
		tmp->index = i;
		i++;
		tmp = tmp->next;
	}
	ft_nb_cmd(param, i);
}

void	ft_nb_cmd(t_parsing *param, int i)
{
	t_parsing	*tmp;

	tmp = param;
	while (tmp)
	{
		tmp->nb_cmd = i;
		tmp = tmp->next;
	}
}
