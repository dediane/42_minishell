/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 22:43:27 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/15 15:59:57 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_parse_env(char *tab, char **key, char **value)
{
	int		dollar;
	int		i;

	i = 0;
	dollar = 0;
	if (tab[i] == '$')
		dollar = 1;
	while (tab[i] && tab[i] != '=')
		i++;
	if (dollar == 1)
		i -= 1;
	*key = ft_strndup(tab, i);
	*value = ft_strchr(tab, '=');
	return (0);
}
//LEAK->HAVE TO FREE l.28

int	ft_is_in_env(char *key, char **envp)
{
	int	i;
	int	size;

	i = -1;
	size = ft_strlen(key);
	while (envp[++i])
	{
		if (ft_strncmp(key, envp[i], size) == 0)
		{
			if (envp[i][size + 1] == '=')
				return (1);
		}
	}
	return (0);
}

void	ft_print_tab(char **tab)
{
	int	i;
	int	j;

	i = -1;
	while (tab[++i])
	{
		j = -1;
		ft_putstr("declare -x ");
		while (tab[i][++j])
			ft_putchar(tab[i][j]);
		ft_putchar('\n');
	}
}
