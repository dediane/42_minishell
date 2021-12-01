/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balkis <balkis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 19:28:36 by ddecourt          #+#    #+#             */
/*   Updated: 2021/12/01 19:02:30 by balkis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

///Diane la plus forte!!, je t'aime!!

int main(int ac, char **av, char **envp)
{
	char *line = NULL;
	t_parsing	param;	
	//t_env		*env; pour envp en liste 

	(void)av;
	(void)envp;
	//(void *)param = NULL;
	//env = NULL;
	if (ac != 1)
		return (ft_putstr("Error: not argument accepted\n"), 1);
	ft_print_title();
	while (1)
	{
		line = readline("\033[1;35m~Minishell$\033[0m ");
		if (!line)
			printf("\nreadline existe pas signal ctrl D, il faut exit\nJe peux pas exit pck la fonction prend en param line, ici line existe pas\n");
		else
		{
			add_history(line);
			printf("signal vaut %d\n", SIGINT);
			signal(SIGINT, ft_sigint);
			signal(SIGQUIT, ft_sigquit);
			(void)param;
			if (ft_strnstr(line, "exit", ft_strlen(line)))
				ft_exit(line);
/*	
			if (line[0] != '\0')
			{
				if (parsing(line, &param)) //return -1 ou 0 si l'allocution echoue ou les quotes ne sont pas fermees ou les > sont plus de deux 
				
					ft_exec_all_cmd(&param, envp);
				}
				//free here
			}
*/
		}
	}
	return (0);
}
