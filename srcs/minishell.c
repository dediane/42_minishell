/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 19:28:36 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/13 00:51:12 by ddecourt         ###   ########.fr       */
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
		{
			puts("HERE I EXIT");
			ft_exit(NULL); //gere le controle D
		}
		else
		{
			if (line)
				add_history(line);
			if (line && ft_strnstr(line, "exit", ft_strlen(line)))
				ft_exit(line);
			if (line && line[0] != '\0')
			{
				if (parsing(line, &param, env)) 
					env = ft_exec_all_cmd(&param, env);
				//free here
			}
		}
	}
	return (0);
}
