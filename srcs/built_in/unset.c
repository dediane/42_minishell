/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:55:03 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/20 11:46:47 by bben-yaa         ###   ########.fr       */
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
		new[i - 1] = line[i];
	}
	new[i - 1] = '\0';
	return (new);
}

char	*ft_get_key(char *arg)
{
	int		i;
	char	*key;

	i = 0;
	while (arg[i] && (ft_isalnum(arg[i]) || arg[i] == '='))
	{
		if (arg[i] == '=')
			break ;
		i++;
	}
	key = ft_strndup(arg, i);
	return (key);
}

char	**unset_in_env(char *line, char **env)
{
	int		i;
	int		j;
	int		size;
	char	*key;
	char	**tmp;

	size = 0;
	i = -1;
	j = 0;
	while (env[++i])
		size++;
	tmp = malloc(sizeof(char *) * (size + 1));
	i = -1;
	while (++i < (size))
	{
		key = ft_get_key(env[i]);
		if (!(ft_strncmp(env[i], line, ft_strlen(line)) == 0 \
		&& ft_strlen(line) == ft_strlen(key)))
			tmp[j++] = ft_strdup(env[i]);
		free(key);
	}
	free_tabs(env);
	tmp[j] = NULL;
	return (tmp);
}

int	ft_is_in_env2(char *key, char **envp)
{
	int	i;
	int	size;

	i = -1;
	size = ft_strlen(key);
	while (envp[++i])
	{
		if (ft_strncmp(key, envp[i], size) == 0)
			return (1);
	}
	return (0);
}

char	**ft_unset(int fd, char **tabs, char **env)
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
	if (!tabs[1] || tabs[2])
		return (env);
	is_in_env = ft_is_in_env2(tabs[1], env);
	if (ft_is_in_env2(tabs[1], env))
		env = unset_in_env(tabs[1], env);
	else
		return (env);
	return (env);
}
