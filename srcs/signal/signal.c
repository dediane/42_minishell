/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 20:11:36 by balkis            #+#    #+#             */
/*   Updated: 2021/12/22 12:31:47 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_sigint(int sig)
{
	(void)sig;
	rl_redisplay();
	write(1, "\n", 1);
	#if __LINUX__
		rl_replace_line("", 0);
	#endif
	#if __APPLE__
		ft_putstr_fd("\033[1;35m~Minishell$\033[0m ", 0);
	#endif
	rl_on_new_line();
	rl_redisplay();
}

void	ft_sigquit(int sig)
{
	(void)sig;
}

void	ft_ignore(int pid)
{
	if (pid == 0)
		printf("diseable\n");//diseable
	else
		printf("ignore\n");//ignore
}

void	ft_relaunch(int pid)
{
	if (pid > 0)
		printf("relaunche signal\n");
	//signal(SIGINT, ft_sigint);
	//signal(SIGQUIT, ft_sigquit);
}
