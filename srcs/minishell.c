/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 19:28:36 by ddecourt          #+#    #+#             */
/*   Updated: 2021/11/24 14:34:59 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int ac, char **av, char **envp)
{
	char *line = NULL;
	t_parsing	param;	

	(void)av;
	(void)envp;
	//param = NULL;
	if (ac != 1)
		return (ft_putstr("Error: not argument accepted\n"), 1);
	while (1)
	{
		line = readline("\033[1;35m Minishell$ \033[0m");
		if (ft_strnstr(line, "exit", ft_strlen(line)))
			ft_exit(line);
		if (line[0] != '\0')
		{
			//ft_pwd(1, envp);
			//ft_cd(envp, "/Users");
			//ft_pwd(1, envp);
			//ft_cd(envp, "/Users/dianedecourt");
			//ft_env(1, envp);
			parsing(line, &param); //return -1 ou 0 si l'allocution echoue ou les quotes ne sont pas fermees ou les > sont plus de deux 
			//ft_exec(line, envp);
		}
	}
	return (0);
}
