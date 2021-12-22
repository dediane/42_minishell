/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:55:05 by ddecourt          #+#    #+#             */
/*   Updated: 2021/12/21 21:15:11 by ddecourt         ###   ########.fr       */
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
	j = -1;
	while (tab[++i])
	{
		j = -1;
		while (tab[i][++j])
			ft_putchar(tab[i][j]);
	}
}

char	**set_in_env(char *line, char **env)
{
	int		i;
	int		size;
	char	**tmp;

	size = 0;
	i = -1;
	while (env[++i])
		size++;
	tmp = malloc(sizeof(char *) * (size + 2));
	i = -1;
	while (++i < size)
	{
		tmp[i] = ft_strdup(env[i]);
	}
	tmp[i] = ft_strdup(line);
	tmp[++i] = NULL;
	return (tmp);
}

/* for(int i=0; i<size_of_array; i++){
	for(int j=0; j<size_of_array-1-i; j++){
	if(strcmp(array[j], array[j+1]) > 0){
		//swap array[j] and array[j+1]
		strcpy(temp, array[j]);
		strcpy(array[j], array[j+1]);
		strcpy(array[j+1], temp);
	  }
	}
  }*/

void	ft_print_export(char **env)
{
	int i;
	int j;
	char *tmp;

	i = -1;
	while (env[++i])
	{
		j = -1;
		while (env[++j])
		{
			if ( env[j + 1] && ft_strncmp(env[j], env[j+ 1], ft_strlen(env[j])))
			{
				tmp = ft_strdup(env[j]);
				env[j] = ft_strdup(env[j + 1]);
				printf("ENV[J] = [%s]\n", env[j]);
				env[j + 1] = ft_strdup(tmp);
				printf("ENV[J + 1] = [%s]\n", env[j + 1]);
			}
		}
		ft_print_tab(env);
	}
}

char	**ft_export(int fd, char **tabs, char **env)
{
	char	*key;
	char	*value;
	char	**tmp;
	int		is_in_env;

	(void)fd;
	key = NULL;
	value = NULL;
	tmp = NULL;
	is_in_env = 0;
	if (!tabs[1])
		ft_print_export(env);
	else if (tabs[2])
		return (0);
	ft_parse_env(tabs[1], &key, &value);
	is_in_env = ft_is_in_env(key, env);
	if (!ft_is_in_env(key, env))
		env = set_in_env(tabs[1], env);
	else
	{
		if (value)
		{
			value = ft_strtrim_first_letter(value);
			change_env(env, key, value);
		}
	}
	return (env);
}
