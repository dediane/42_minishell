/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 19:27:16 by ddecourt          #+#    #+#             */
/*   Updated: 2021/11/09 20:03:15 by ddecourt         ###   ########.fr       */
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
	char	**cmd;
	char	**arg;
	int		pipe;
}			t_parsing;

//exec
void	ft_exec(char *line, char **envp);

//parsing
int	parsing(char *argv);

//built_in
int	ft_env(int fd, char **envp);
int	ft_pwd(int fd, char** envp);

#endif
