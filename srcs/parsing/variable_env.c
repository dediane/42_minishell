/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:18:28 by balkis            #+#    #+#             */
/*   Updated: 2022/01/20 14:42:37 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*find_var(char **envp, char *line)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	j = -1;
	while (envp[++j])
	{
		while (envp[j][i] != '=')
			i++;
		var = strndup(envp[j], i);
		if (ft_strncmp(var, &line[1], ft_strlen(line)) == 0)
		{
			free(var);
			return (ft_copy_line(line, envp, i, j));
		}
		i = 0;
		free(var);
		var = NULL;
	}
	free(line);
	line = NULL;
	line = ft_line(line, ' ');
	return (line);
}

int	dolar_quotes(char *line)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_change(char *argv)
{
	int	i;

	i = 0;
	if (argv[i] == '$' && ((argv[i + 1] && argv[i + 1] == ' ' ) \
		|| (!argv[i + 1])))
		return (0);
	while (argv[i] && argv[i] != ' ')
	{
		if (argv[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_replace_var(char *line, char **envp)
{
	int		len;
	int		pos;
	char	*var;
	char	*exp;

	len = 0;
	pos = 0;
	exp = line;
	while (line[len])
	{
		if (line[len] == '$')
		{
			pos = len + 1;
			len = pos_dolar(line);
			break ;
		}
		len++;
	}
	if (!len)
		return (line);
	var = strndup(&line[pos], len);
	exp = ft_search_var(var, envp, exp, pos);
	var = malloc(sizeof(char) * \
		(pos + ft_strlen(exp) + ft_strlen(&line[pos + len]) + 1));
	return (ft_copy(var, line, exp, pos));
}

char	*ft_search_var(char *var, char **envp, char *line, int pos)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	j = -1;
	name = NULL;
	(void)pos;
	(void)line;
	while (envp[++j])
	{
		while (envp[j][i] != '=')
			i++;
		name = strndup(envp[j], i);
		if (ft_strncmp(name, var, ft_strlen(name)) == 0 && \
			ft_strncmp(name, var, ft_strlen(var)) == 0)
		{
			free(name);
			return (ft_copy_var(var, envp, j, i));
		}
		ft_la(&i, name);
	}
	return (ft_var(var));
}
