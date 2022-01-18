/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 19:28:36 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/18 11:42:54 by bben-yaa         ###   ########.fr       */
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
	}
	env[i] = NULL;
	return (env);
}

char	*ft_readline_signal(char *line)
{
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigquit);
	line = readline("\033[1;35m~Minishell$\033[0m ");
	if (!line)
		ft_exit(NULL);
	return (line);
}

void	line_hyst(char *line)
{
	if (line)
		add_history(line);
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	char		**env;
	t_parsing	param;

	g_exit_value = 0;
	(void)av;
	line = NULL;
	env = ft_copy_tab(envp);
	if (ac != 1)
		return (ft_putstr("Error: not argument accepted\n"), 1);
	ft_print_title();
	while (1)
	{
		line = ft_readline_signal(line);
		line_hyst(line);
		if (line[0] != '\0')
		{
			if (parsing(line, &param, env) && check_heredoc(&param, env))
				env = ft_exec_all_cmd(&param, env);
			else
				ft_free_params(&param);
		}
	}
	return (0);
}
