/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:55:05 by ddecourt          #+#    #+#             */
/*   Updated: 2021/12/14 19:15:29 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_parse_export(char *tab)
{
	char	*key;
	char	*value;
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
	key = ft_strndup(tab, i);
	value = ft_strchr(tab, '=');
	printf("%s\n", key);
	printf("%s\n", value);
	return (0);
}

int ft_export(int fd, char *tabs)
{
	// 1 - check if $ ou pas $
			// if $ -> mettre dans un char *tmp les caracteres jusqu'au = et char *value jusqu'a la fin ( parser les quotes)
				//check si tmp est dans env
					//si oui return 0 si non return 1 
			// if pas dollar -> mettre dans un char *tmp les caracteres jusqu'au =
	ft_parse_export(tabs);
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