/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 19:27:16 by ddecourt          #+#    #+#             */
/*   Updated: 2021/11/10 12:26:19 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef	struct s_parsing
{
	int		nb_cmd;
	char	**tabs; //il y a la commande et les arguments dedans
	int		pipe;
}			t_parsing;

//exec
void	ft_exec(char *line, char **envp);

//parsing
int	parsing(char *argv);
#endif
