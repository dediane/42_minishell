


                ////HEADER////



#include "../../inc/minishell.h"


///////// A voir //////

int	env_list(t_env  **env, char **envp)
{
	t_env	*tmp;
	int		y;

	y = 0;
	(void)envp;
	printf("hello env = %p\n", &env);
    while (envp[y])
    {
		if (!ft_malloc_env(env))
			return (0);
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		ft_find_variable(tmp, envp[y]);
		printf("envp variable vaut %s\n", tmp->variable);
		printf("envp var_def vaut %s\n", tmp->var_def);
		printf("\nenvp[%d] %s\n", y, envp[y]);
    	/*--> malloc un maillon ft_malloc_env(env);
        --> malloc name et interpretation_name, puis dans le maillon mettre dans name touut ce qui a avant le '='
			et mettre dans interpretation_name touut ce qui a apres '='*/
        y++;
    }
	int i = 0;
	t_env *tmp2;
	tmp2 = *env;

	while(tmp2)
	{
		printf("variable %s\n", tmp2->variable);
		printf("var_def %s\n", tmp2->var_def);
		printf("boucle %d\n", i);
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
		return (0);		//il faut aussi free toute la liste 
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
	int i;

	i = 0;
	while(envp[i] != '=')
		i++;
	env->variable = ft_strndup(envp, i);
	i++;		//on se situe juste apres le '='
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