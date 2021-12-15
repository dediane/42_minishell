/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:55:05 by ddecourt          #+#    #+#             */
/*   Updated: 2021/12/15 12:51:46 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_parse_export(char *tab, char **key, char **value)
{
	int		dollar;
	int		i;

	i = 0;
	dollar = 0;
	if (tab[i] == '$')
		dollar = 1;
	while (tab[i] != '=')
		i++;
	if (dollar == 1)
		i -= 1;
	*key = ft_strndup(tab, i);
	*value = ft_strchr(tab, '=');
	return (0);
}

int ft_export(int fd, char *tabs)
{
	char	*key;
	char	*value;
	
	key = NULL;
	value = NULL;
	/*if (tabs[2])
		return (0);*/
	ft_parse_export(tabs, &key, &value);
	printf("%s\n", key);
	printf("%s\n", value);
	(void) fd;
	/*int i;
	int j;
	int size;

	i = 1;
	j = -1;
	size = ft_strlen(tabs[i]);
	if (tabs[i][++j] == '$')
		return(0);
	while (tabs[i][j] != '=')
		j++;
	if ()*/
	return (0);
}