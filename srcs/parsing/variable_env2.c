/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_env2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balkis <balkis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:21:35 by balkis            #+#    #+#             */
/*   Updated: 2021/12/21 22:07:42 by balkis           ###   ########.fr       */
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
