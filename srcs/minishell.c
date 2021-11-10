/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 19:28:36 by ddecourt          #+#    #+#             */
/*   Updated: 2021/11/10 16:04:45 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int ac, char **av, char **envp)
{
	char *line = NULL;

	(void)av;
	(void)envp;
	if (ac != 1)
		return (ft_putstr("Error: not argument accepted\n"), 1);
	while (1)
	{
		line = readline("\033[1;35m Minishell$ \033[0m");
		if (line[0] != '\0' || ft_strnstr("exit", line, 4) == 0)
		{
			parsing(line);
			//ft_env(1, envp);
			// ft_pwd(1, envp);
			//ft_exec(line, envp);
		}
		//if(ft_strnstr("exit", line, 4))
		//	exit(1);
		/*printf("minishell $ - ");
		readline();
		//get_next_line(1, &line);
		printf("%s\n", line);*/
	}
	return (0);
}
