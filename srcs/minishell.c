/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 19:28:36 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/11 22:41:53 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_exit_value;

void	ft_print_title(void)
{
	printf("\033[1;35m\
	 __  __ _       _     _          _ _ \n\
	|  \\/  (_)_ __ (_)___| |__   ___| | |\n\
	| |\\/| | | '_ \\| / __| '_ \\ / _ \\ | |\n\
	| |  | | | | | | \\__ \\ | | |  __/ | |\n\
	|_|  |_|_|_| |_|_|___/_| |_|\\___|_|_|\n\033[0m \
	\t\t\tby Diane & Balkis\n\n");
}

char	**ft_copy_tab(char **envp)
{
	int		i;
	int		size;
	char	**env;

	size = 0;
	i = -1;
	while (envp[++i])
		size++;
	env = malloc(sizeof(char *) * (size + 1));
	i = -1;
	while (++i < size)
	{
		env[i] = envp[i];
		//env[i] = ft_strjoin(env[i], "\n");
	}
	env[i] = NULL;
	return (env);
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	char		**env;
	t_parsing	param;
	//t_env		*env; pour envp en liste 

	(void)av;
	g_exit_value = 0;
	line = NULL;
	env = ft_copy_tab(envp);
	//env = set_ret_value(env);
	//(void *)param = NULL;
	//env = NULL;
	if (ac != 1)
		return (ft_putstr("Error: not argument accepted\n"), 1);
	ft_print_title();
	while (1)
	{
		signal(SIGINT, ft_sigint);
		signal(SIGQUIT, ft_sigquit);
		line = readline("\033[1;35m~Minishell$\033[0m ");
		if (!line)
			ft_exit(NULL); //gere le controle D
		else
		{
			if (line)
				add_history(line);
			if (ft_strnstr(line, "exit", ft_strlen(line)))
			//if (ft_strncmp(line, "exit", ft_strlen(line)) == 0)
				ft_exit(line);
			if (line[0] != '\0')
			{
				//printf("line[0] vaut %c\n", line[0]);
				if (parsing(line, &param, env)) //return -1 ou 0 si l'allocution echoue, les quotes ne sont pas fermees, 
					// les > sont plus de deux, y'a rien apres les pipes (faut regarder le comportement de bash pck pour lui c'est pas une erreur),
					// y'a aucun fichier après les redirection 
				{
					env = ft_exec_all_cmd(&param, env);
				}
				//free here
			}
		}
	}
	return (0);
}
