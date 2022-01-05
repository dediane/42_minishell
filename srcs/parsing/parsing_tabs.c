/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tabs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balkis <balkis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:08:21 by balkis            #+#    #+#             */
/*   Updated: 2021/12/21 21:42:43 by balkis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_paste_tab(t_parsing *param, char **new, char *line)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (param->tabs[y])
	{
		new[y] = malloc(sizeof(char) * (ft_strlen(param->tabs[y]) + 1));
		if (!new[y])
			return (0);
		while (param->tabs[y][i])
		{	
			new[y][i] = param->tabs[y][i];
			i++;
		}
		new[y][i] = '\0';
		i = 0;
		y++;
	}
	new[y] = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!new[y])
		return (0);
	ft_strcpy(new[y], line);
	new[++y] = NULL;
	return (1);
}

void	free_tabs(char **tabs)
{
	int	i;

	i = 0;
	if (tabs)
	{
		while (tabs[i])
		{
			if (tabs[i])
			{
				free(tabs[i]);
				tabs[i] = NULL;
			}
			i++;
		}
	}
	free(tabs);
	tabs = NULL;
}

char	**ft_malloc_tab(t_parsing *param, int len_tab, char *line)
{
	char	**new;

	if (len_tab == 0)
	{
		new = malloc(sizeof(char *) * 2);
		if (!new)
			return (0);
		new[0] = malloc(sizeof(char) * (ft_strlen(line) + 1));
		if (!new[0])
			return (0);
		ft_strcpy(new[0], line);
		new[1] = NULL;
		free(line);
		return (new);
	}
	new = malloc(sizeof(char *) * (len_tab + 2));
	if (!new)
		return (0);
	ft_paste_tab(param, new, line);
	free(line);
	free_tabs(param->tabs);
	return (new);
}

int	ft_tabs(t_parsing *param, char *line)
{
	int	len_tab;

	len_tab = ft_len_tabs(param->tabs);
	param->tabs = ft_malloc_tab(param, len_tab, line);
	if (!param->tabs)
		return (0);
	return (1);
}

int	ft_len_tabs(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}
