/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_liste.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balkis <balkis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 19:08:24 by balkis            #+#    #+#             */
/*   Updated: 2021/12/27 19:13:51 by balkis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	env_list(t_env **env, char **envp)
{
	t_env	*tmp2;
	t_env	*tmp;
	int		y;
	int		i;

	y = 0;
	i = 0;
	tmp2 = *env;
	while (envp[y])
	{
		if (!ft_malloc_env(env))
			return (0);
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		ft_find_variable(tmp, envp[y]);
		y++;
	}
	while (tmp2)
	{
		i++;
		tmp2 = tmp2->next;
	}
	return (1);
}

int	ft_malloc_env(t_env	**env)
{
	t_env	*tmp;
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
	{
		free_env(env);
		return (0);
	}
	if (*env == NULL)
	{
		*env = new;
		new->next = NULL;
		new->variable = NULL;
		new->var_def = NULL;
	}
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->next = NULL;
		new->variable = NULL;
		new->var_def = NULL;
	}
	return (1);
}

int	ft_find_variable(t_env *env, char *envp)
{
	int	i;

	i = 0;
	while (envp[i] != '=')
		i++;
	env->variable = ft_strndup(envp, i);
	i++;
	env->var_def = ft_strdup(&(envp[i]));
	return (1);
}

void	free_env(t_env **env)
{
	t_env	*tmp;

	while ((*env) != NULL)
	{
		tmp = (*env);
		(*env) = (*env)->next;
		free(tmp->variable);
		free(tmp->var_def);
		free(tmp);
	}
}
