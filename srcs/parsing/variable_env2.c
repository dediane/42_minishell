/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_env2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:21:35 by balkis            #+#    #+#             */
/*   Updated: 2022/01/21 10:34:46 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_copy_line(char *line, char **envp, int i, int j)
{
	free(line);
	line = NULL;
	line = ft_strdup(&envp[j][++i]);
	return (line);
}

char	*ft_copy_var(char *var, char **envp, int j, int i)
{
	free(var);
	var = NULL;
	var = ft_strdup(&envp[j][++i]);
	return (var);
}

void	ft_la(int *i, char *name)
{
	(*i) = 0;
	free(name);
	name = NULL;
}

char	*ft_var(char *var)
{
	free(var);
	var = NULL;
	var = ft_strdup(" ");
	return (var);
}
