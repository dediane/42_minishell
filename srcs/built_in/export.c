/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:55:05 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/16 13:20:25 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
//LEAK->HAVE TO FREE l.25
//LEAK->HAVE TO FREE l.29
//LEAK->HAVE TO FREE l.31

void	ft_print_export(char **env)
{
	char	**copy;
	char	*tmp;
	int		i;
	int		j;

	copy = ft_copy_tab(env);
	i = 0;
	while (copy[i])
	{
		j = i + 1;
		while (copy[j])
		{
			if (ft_strncmp(copy[i], copy[j], ft_strlen(copy[i])) > 0)
			{
				tmp = ft_strdup(copy[i]);
				copy[i] = ft_strdup(copy[j]);
				copy[j] = ft_strdup(tmp);
			}
			j++;
		}
		i++;
	}
	ft_print_tab(copy);
	free_tabs(copy);
	free(tmp);
}
//LEAK->HAVE TO FREE l.56
//LEAK->HAVE TO FREE l.57

int	ft_check_arg(char	*arg)
{
	int	i;

	i = 0;
	while (arg[i] && ft_isalpha(arg[i]))
		i++;
	if (i == ft_strlen(arg) || (arg[i + 1] && arg[i + 1] == '='))
		return (1);
	ft_putstr_fd("minishell: export: `", 1);
	ft_putstr_fd(arg, 1);
	ft_putstr_fd("': not a valid identifier\n", 1);
	return (0);
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
	{
		ft_print_export(env);
		return (env);
	}
	else if (tabs[2])
		return (0);
	//if (!ft_check_arg(tabs[1]))
	//	return (0);
	ft_parse_env(tabs[1], &key, &value);
	//is_in_env = ft_is_in_env(key, env);
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
