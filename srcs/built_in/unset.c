/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:55:03 by ddecourt          #+#    #+#             */
/*   Updated: 2021/12/19 22:06:03 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strtrim_first_letter(char *line)
{
	char	*new;
	int		i;
	
	i = 0;
	new = malloc(sizeof(char) * ft_strlen(line));
	while (line[++i])
	{
		new[i - 1]  =line[i];
	}
	new[i - 1] = '\0';
	return (new);
}

char	**unset_in_env(char *line, char **env)
{
	
	int i;
	int j;
	int size;
	int size_line;
	char **tmp;
	
	size = 0;
	i = -1;
	j = 0;
	while (env[++i])
		size++;
	tmp = malloc(sizeof(char *) * (size));
	i = -1;
	//printf("Line = %s\n", line);
	while (++i < (size - 1))
	{
		size_line = ft_strlen(line);
		if (!(ft_strncmp(env[i], line, size_line) == 0))
			tmp[j++] = ft_strdup(env[i]);
	}
	tmp[j] = NULL;
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
	{
		env = unset_in_env(tabs[1], env);
		printf("I am here\n");
		ft_print_tab(env);
	}
	else
		return (0);
	return (env);
}