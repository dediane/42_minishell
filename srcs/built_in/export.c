/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:55:05 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/18 14:46:26 by ddecourt         ###   ########.fr       */
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
	free(env);
	return (tmp);
}

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
				tmp = copy[i];
				copy[i] = copy[j];
				copy[j] = tmp;
			}
			j++;
		}
		i++;
	}
	ft_print_tab(copy);
	free(copy);
}

int	ft_check_arg(char	*arg)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	if ((arg[i] && (arg[i] >= '0' && arg[i] <= '9')) || \
	(arg[0] && arg[0] == '$'))
	{
		ft_putstr_fd("minishell: export: `", 1);
		ft_putstr_fd(arg, 1);
		ft_putstr_fd("': not a valid identifier\n", 1);
		g_exit_value = 1;
		return (0);
	}
	while (arg[i] && (ft_isalnum(arg[i]) || arg[i] == '='))
	{
		if (arg[i] == '=')
			flag = 1;
		i++;
	}
	if (i == ft_strlen(arg) && flag)
		return (1);
	return (0);
}

char	**ft_export(char **tabs, char **env)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	if (!tabs[1])
	{
		ft_print_export(env);
		return (env);
	}
	else if (tabs[2])
		return (0);
	if (!ft_check_arg(tabs[1]))
		return (env);
	ft_parse_env(tabs[1], &key, &value);
	if (!ft_is_in_env(key, env))
		env = set_in_env(tabs[1], env);
	else if (value)
	{
		value = ft_strtrim_first_letter(value);
		change_env(env, key, value);
	}
	free(key);
	return (env);
}
