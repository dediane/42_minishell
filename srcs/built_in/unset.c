/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:55:03 by ddecourt          #+#    #+#             */
/*   Updated: 2021/12/19 17:33:09 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**unset_in_env(char *line, char **env)
{
	
	int i;
	int size;
	char **tmp;
	
	size = 0;
	i = -1;
	while (env[++i])
		size++;
	tmp = malloc(sizeof(char *) * (size));
	i = -1;
	while (++i < (size - 1))
	{
        if (!(ft_strncmp(env[i], line, ft_strlen(line)) == 0))
			tmp[i] = ft_strdup(env[i]);
	}
	tmp[i] = NULL;
	return (tmp);
}

char **ft_unset(int fd, char **tabs, char **env)
{
	char	*key;
	char	*value;
	char	**tmp;
	int		i;
	int		is_in_env;
	
	(void)fd;
	key = NULL;
	value = NULL;
	tmp = NULL;
	is_in_env = 0;
	i = -1;
	if (tabs[2])
		return (0);
	is_in_env = ft_is_in_env(tabs[1], env);
	if (ft_is_in_env(tabs[1], env))
		env = unset_in_env(tabs[1], env);
	else
		return (0);
	return (env);
}