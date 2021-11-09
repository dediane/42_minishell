/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 19:28:36 by ddecourt          #+#    #+#             */
/*   Updated: 2021/11/09 12:43:15 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int ac, char **av, char **envp)
{
	char *line = NULL;

	(void)av;
	if (ac != 1)
		return (ft_putstr("Error: not argument accepted\n"), 1);
	while (1)
	{
		line = readline( "Minishell$ " );
		if (line[0] != '\0')
		{
			parsing(line);
			ft_exec(line, envp);
		}
		/*printf("minishell $ - ");
		readline();
		//get_next_line(1, &line);
		printf("%s\n", line);*/
	}
	return (0);
}
